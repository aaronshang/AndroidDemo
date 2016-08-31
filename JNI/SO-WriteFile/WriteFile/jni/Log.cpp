//
//  Log.cpp
//  StatisticAnalysisLib
//
//  Created by Kevin on 3/9/15.
//  Copyright (c) 2015 Aaron. All rights reserved.
//

#include "Log.h"
#include <pthread.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>


#ifdef _ANDROID
#include <android/log.h>
#include <jni.h>
#define  LOG_TAG    "libSA"
#endif


#define __WalktourLog__

//日志文件名 （全路径）
//#define WalktourLogFile "/var/root/datacenter.log"
extern string g_logFileName;

pthread_mutex_t mutex_printlog = PTHREAD_MUTEX_INITIALIZER;
bool  write_log_flag = true;    //是否写log文件


/*************************************************
 Function:       usseconds_from
 Description:    获取当前时间距start_time的时间差
 Input:          struct timeval 起始时间
 Output:
 Return:         时间差 （微秒）
 Others:
 *************************************************/

double  usseconds_from(const struct timeval  start_time)
{
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    
    double delay = (time_now.tv_sec - start_time.tv_sec)*1000000 +
    (time_now.tv_usec - start_time.tv_usec);
    
    return delay;
}

/*************************************************
 Function:       seconds_from
 Description:    获取当前时间距start_time的时间差
 Input:          time_t 起始时间
 Output:
 Return:         时间差 （秒）
 Others:
 *************************************************/

double  seconds_from(time_t  start_time)
{
    time_t time_now = time(NULL);
    return difftime(time_now, start_time);
}

/*************************************************
 Function:       convert_time_format
 Description:    flag:1 yyyy-mm-dd hh:mm:ss.sss
 2 hh:mm:ss.sss
 Input:
 Output:
 Return:
 Others:
 *************************************************/

string  convert_time_format(struct timeval time_val, int flag)
{
    tm* tm_ptr = localtime(&time_val.tv_sec);
    
    string ret_time;
    char   time_buf[50];
    memset(time_buf, 0, 50);
    
    switch (flag) {
        case 1:
            sprintf(time_buf, "%4d-%02d-%02d %02d:%02d:%02d.%03d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, time_val.tv_usec/1000);
            break;
        case 2:
            sprintf(time_buf, "[%02d-%02d %02d:%02d:%02d.%03d]", tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, time_val.tv_usec/1000);
            break;
        case 3:
            sprintf(time_buf, "[%02d:%02d:%02d.%03d]", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, time_val.tv_usec/1000);
            break;
        case 4:
            sprintf(time_buf, "[%02d-%02d %02d:%02d:%02d.%04d]", tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, time_val.tv_usec/100);
            break;
        case 5:
            sprintf(time_buf, "%02d:%02d:%02d", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
            break;
        case 6:
            sprintf(time_buf, "%4d%02d%02d%02d%02d%02d", tm_ptr->tm_year+1900, tm_ptr->tm_mon+1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
            break;
        case 7:
            sprintf (time_buf, "%4d%02d%02d-%02d%02d%02d",
                     1900+tm_ptr->tm_year,
                     1+tm_ptr->tm_mon,
                     tm_ptr->tm_mday,
                     tm_ptr->tm_hour,
                     tm_ptr->tm_min,
                     tm_ptr->tm_sec);
            break;
        case 8:
            sprintf (time_buf, "%4d-%02d-%02d-%02d-%02d-%02d",
                     1900+tm_ptr->tm_year,
                     1+tm_ptr->tm_mon,
                     tm_ptr->tm_mday,
                     tm_ptr->tm_hour,
                     tm_ptr->tm_min,
                     tm_ptr->tm_sec);
            break;
        case 9:
            sprintf (time_buf, "%4d-%02d-%02d %02d:%02d:%02d",
                     1900+tm_ptr->tm_year,
                     1+tm_ptr->tm_mon,
                     tm_ptr->tm_mday,
                     tm_ptr->tm_hour,
                     tm_ptr->tm_min,
                     tm_ptr->tm_sec);
            break;
        default:
            sprintf(time_buf, "[%02d:%02d:%02d.%03d]", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, time_val.tv_usec/1000);
            break;
    }
    ret_time = time_buf;
    return ret_time;
}

string  convert_time_format(time_t time, int flag)
{
    struct timeval time_val;
    time_val.tv_sec = time;
    return convert_time_format(time_val, flag);
}

bool write_log(const char* buffer)
{
    FILE*  fp_log = NULL;
    fp_log = fopen(g_logFileName.c_str(), "at+");
    if (fp_log != NULL)
    {
        fwrite(buffer, sizeof(char), strlen(buffer), fp_log);
        fflush(fp_log);
        fclose(fp_log);
    }else{
#ifdef _ANDROID
        __android_log_write(ANDROID_LOG_INFO,LOG_TAG, "write_log fail");
#else
        printf("[Warning]write log error!\n");
#endif
    }
    
    return true;
}

/*************************************************
 Function:      PrintError
 Description:
 Input:
 Output:
 Return:
 Others:
 *************************************************/
void PrintError(const char* str, ...)
{
#ifndef __WalktourLog__
    return;
#endif
    pthread_mutex_lock(&mutex_printlog);
    
    char  print_buffer[1056] = {0};  //PrintLog缓冲
    char  thread_name[128] = {0};
    string timestr;
    struct timeval tm_val;
    __uint64_t tid = 0;
//    pthread_threadid_np(pthread_self(), &tid);
//    pthread_getname_np(pthread_self(), thread_name, 128);
    gettimeofday(&tm_val, NULL);
    timestr = convert_time_format(tm_val, 4);
    sprintf(print_buffer, "[%llX %s]%s [Error]", tid, thread_name, timestr.c_str());
    long timestr_len = strlen(print_buffer);
    //    printf("PrintLog:%s\n", str);
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(print_buffer+timestr_len, 1000, str, argptr);
    va_end(argptr);
    
    sprintf(print_buffer+strlen(print_buffer), "\r\n");
    
#ifdef _ANDROID
    __android_log_write(ANDROID_LOG_INFO,LOG_TAG,print_buffer);
#else
    printf("%s", print_buffer);
#endif
    
    if (write_log_flag) {
        write_log(print_buffer);
    }
    
    pthread_mutex_unlock(&mutex_printlog);
}

/*************************************************
 Function:      PrintLog
 Description:
 Input:
 Output:
 Return:
 Others:
 *************************************************/
void PrintLog(const char* str, ...)
{
#ifdef _ANDROID
    
    __android_log_write(ANDROID_LOG_INFO,LOG_TAG,str);
    
#endif
#ifndef __WalktourLog__
    return;
#endif
    
    pthread_mutex_lock(&mutex_printlog);
    
    char  print_buffer[1024] = {0};  //PrintLog缓冲
    char  thread_name[128] = {0};
    string timestr;
    struct timeval tm_val;
    __uint64_t tid = 0;
//    pthread_threadid_np(pthread_self(), &tid);
//    pthread_getname_np(pthread_self(), thread_name, 128);
    gettimeofday(&tm_val, NULL);
    timestr = convert_time_format(tm_val, 4);
    sprintf(print_buffer, "[%llX %s]%s ", tid, thread_name, timestr.c_str());
    long timestr_len = strlen(print_buffer);
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(print_buffer+timestr_len, 1000, str, argptr);
    va_end(argptr);
    
    sprintf(print_buffer+strlen(print_buffer), "\r\n");
    
#ifdef _ANDROID
    __android_log_write(ANDROID_LOG_INFO,LOG_TAG,print_buffer);
#else
    printf("%s", print_buffer);

#endif
    if (write_log_flag) {
//        if (get_file_size(g_logFileName.c_str()) >= (31457280))  //大小限制 30MB
//        {
//            //(10MB)
//            interceptionFile(10485760, g_logFileName.c_str(), g_logFileName.c_str());
//        }
        
        write_log(print_buffer);
    }

    pthread_mutex_unlock(&mutex_printlog);
}

//截取文件后面iSize大小的数据
void interceptionFile(long iSize, const char* pSrcFile, const char* pDesFile)
{
//    printf("interceptionFile start\n");
    FILE* fp_log = fopen(pSrcFile, "r");
    if (fp_log == NULL)
    {
        return;
    }
    
    char* pTempData = (char*)malloc(iSize+1);
    memset(pTempData, 0, iSize+1);
    
    fseek(fp_log, -1L*iSize, SEEK_END);
    iSize = fread(pTempData, sizeof(char), iSize, fp_log);
    fclose(fp_log);
    fp_log = 0;
    
    fp_log = fopen(pDesFile, "w");
    if (fp_log == NULL)
    {
        free(pTempData);
        pTempData = NULL;
        return;
    }
    
    fwrite(pTempData, sizeof(char), iSize, fp_log);
    fflush(fp_log);
    fclose(fp_log);
    
    free(pTempData);
    pTempData = NULL;
//    printf("interceptionFile end\n");
}


/*************************************************
 Function:      get_file_path
 Description:   获取文件路径
 Input:         全文件名
 Output:        文件路径
 Return:        指向最后一个‘/’的指针
 Others:
 *************************************************/

const char* get_file_path(const char* file_name, char* file_path)
{
    if (file_name == NULL || file_path == NULL) {
        PrintLog("get_file_path file_name null");
        return NULL;
    }
    char* pStr = (char*)file_name;
    char* pRet = const_cast<char*>(get_short_file_name(file_name));
    if (pRet!=NULL && strlen(file_name)>strlen(pRet)) {
        
        strncpy(file_path, file_name, strlen(file_name)-strlen(pRet));
        *(file_path+strlen(file_name)-strlen(pRet)+1) = '\0';
        pStr += strlen(file_name)-strlen(pRet);
    }else{
        *file_path = '\0';
    }
    return pStr;
}

/*************************************************
 Function:      get_short_file_name
 Description:   获取文件名
 Input:         全文件名
 Output:
 Return:        指向文件名起点的指针
 Others:
 *************************************************/

const char* get_short_file_name(const char* file_name)
{
    if (file_name ==NULL || strlen(file_name) <= 0) {
        PrintLog("get_short_file_name file_name null");
        return "";
    }
    char* pStr = (char*)file_name + strlen(file_name)-1;
    
    while (pStr>=file_name && *pStr != '/'){
        pStr--;
    }
    pStr++;
    return pStr;
}

/*************************************************
 Function:      get_file_extension
 Description:   获取文件扩展名
 Input:         全文件名
 Output:
 Return:        指向文件扩展名起点的指针
 Others:
 *************************************************/

const char* get_file_extension(const char* file_name)
{
    if (file_name ==NULL) {
        PrintLog("get_file_extension file_name null");
        return NULL;
    }
    char* pStr = (char*)file_name + strlen(file_name);
    
    if (strlen(file_name) <= 0 || *(pStr-1) == '.') {
        return "";
    }
    
    while (--pStr != file_name){
        
        if (*pStr == '.' ) {
            
            return pStr;
        }
    }
    
    return "";
}


/*************************************************
 Function: file_rename
 Description:
 Input:    oldname,   newname
 Output:
 Return:   bool
 Others:
 *************************************************/

bool file_rename(const char* oldname, const char* newname)
{
    if (oldname==NULL||newname==NULL) {
        PrintLog("file_rename null");
        return false;
    }
    if (strcmp(oldname, newname) != 0){
        rename(oldname, newname);
        remove(oldname);
    }
    return true;
}


/*************************************************
 Function: change_extension
 Description:
 Input:    file_name,   new extension
 Output:
 Return:   0 成功，其他失败
 Others:
 *************************************************/

int change_extension(char* file_name, const char* extension)
{
    if (file_name==NULL||extension==NULL) {
        return -1;
    }
    
    char* ptr = const_cast<char*>(get_file_extension(file_name));
    
    if (ptr==NULL || strlen(ptr)<=0) {
        
        return -1;
    }
    strcpy(ptr, extension);
    return 0;
}



/*************************************************
 Function:      get_file_size
 Description:
 Input:
 Output:
 Return: file size in bytes
 Others:  error reutrn -1
 *************************************************/
long get_file_size(const char *str_file_name)
{
    FILE* file_ptr = NULL;
    long file_size = -1;
    
    if(str_file_name == NULL || strlen(str_file_name) < 1)
    {
        
#ifdef _ANDROID
//        __android_log_write(ANDROID_LOG_INFO,LOG_TAG, "get_file_size fail");
#else
        printf("get_file_size fail, filename:%s\n", str_file_name);
#endif
        return file_size;
    }
    
    struct stat info;
    if (stat(str_file_name, &info) == 0) {
        file_size = (long)info.st_size;
    }else{
        
#ifdef _ANDROID
        __android_log_write(ANDROID_LOG_INFO,LOG_TAG, "－－－－－get_file_size fail");
        __android_log_write(ANDROID_LOG_INFO,LOG_TAG, str_file_name);
#else
        printf("get_file_size fail, filename:%s\n", str_file_name);
#endif
        
        file_ptr = fopen(str_file_name, "rb");
        
        if (file_ptr != NULL)
        {
            fseek(file_ptr, 0, SEEK_END);
            file_size = ftell(file_ptr);
            fclose(file_ptr);
        }else{
            
            
#ifdef _ANDROID
            __android_log_write(ANDROID_LOG_INFO,LOG_TAG, "get_file_size open fail");
#else
           printf("get_file_size %s open fail\n", str_file_name);
#endif
        }
    }
    
    return file_size;
}


void CreateProcess(const char *cmd){
    
    pid_t pid = vfork();
    if (pid<0) {
        PrintLog("[Warning]CreateProcess vfork failure!");
        return;
    }
    if (pid == 0) {
        int ret = 0;
        ret = execl("/bin/sh", "sh", "-c", cmd, (char*)NULL);
        _exit(255);
    }
    pid = waitpid(0, NULL, 0);
}



