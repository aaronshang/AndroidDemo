//
//  Log.h
//  StatisticAnalysisLib
//
//  Created by Kevin on 3/9/15.
//  Copyright (c) 2015 Aaron. All rights reserved.
//

#ifndef __StatisticAnalysisLib__Log__
#define __StatisticAnalysisLib__Log__

#include <stdio.h>
#include <string>
#include <sys/time.h>

using namespace std;

#define msleep(msec) (usleep((msec)*1000))

/*************************************************
 Function:      PrintLog
 Description:
 Input:
 Output:
 Return:
 Others:
 *************************************************/

void PrintLog(const char* str, ...);



/*************************************************
 Function:      PrintError
 Description:
 Input:
 Output:
 Return:
 Others:
 *************************************************/

void PrintError(const char* str, ...);


//截取文件后面iSize大小的数据
void interceptionFile(long iSize, const char* pSrcFile, const char* pDesFile);


/*************************************************
 Function:       convert_time_format
 Description:    flag:1 yyyy-mm-dd hh:mm:ss.sss
 2 hh:mm:ss.sss
 Input:
 Output:
 Return:
 Others:
 *************************************************/

string  convert_time_format(struct timeval time_val, int flag);
string  convert_time_format(time_t time, int flag);

/*************************************************
 Function:      get_file_path
 Description:   获取文件路径
 Input:         全文件名
 Output:        文件路径
 Return:        指向最后一个‘/’的指针
 Others:
 *************************************************/

const char* get_file_path(const char* file_name, char* file_path);

/*************************************************
 Function:      get_short_file_name
 Description:   获取文件名
 Input:         全文件名
 Output:
 Return:        指向文件名起点的指针
 Others:
 *************************************************/

const char* get_short_file_name(const char* file_name);


/*************************************************
 Function:      get_file_extension
 Description:   获取文件扩展名
 Input:         全文件名
 Output:
 Return:        指向文件扩展名起点的指针
 Others:
 *************************************************/

const char* get_file_extension(const char* file_name);


/*************************************************
 Function: file_rename
 Description:
 Input:    oldname,   newname
 Output:
 Return:   bool
 Others:
 *************************************************/

bool file_rename(const char* oldname, const char* newname);


/*************************************************
 Function: change_extension
 Description:
 Input:    file_name,   new extension
 Output:
 Return:   0 成功，其他失败
 Others:
 *************************************************/

int change_extension(char* file_name, const char* extension);


/*************************************************
 Function:      get_file_size
 Description:
 Input:
 Output:
 Return: file size in bytes
 Others:  error reutrn -1
 *************************************************/

long get_file_size(const char *str_file_name);

void CreateProcess(const char *cmd);


/*************************************************
 Function:       usseconds_from
 Description:    获取当前时间距start_time的时间差
 Input:          struct timeval 起始时间
 Output:
 Return:         时间差 （微秒）
 Others:
 *************************************************/

double  usseconds_from(const struct timeval  start_time);

/*************************************************
 Function:       seconds_from
 Description:    获取当前时间距start_time的时间差
 Input:          time_t 起始时间
 Output:
 Return:         时间差 （秒）
 Others:
 *************************************************/

double  seconds_from(time_t  start_time);



#endif /* defined(__StatisticAnalysisLib__Log__) */
