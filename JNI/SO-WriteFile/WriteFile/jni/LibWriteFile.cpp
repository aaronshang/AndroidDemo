//
//  LibWriteFile.cpp
//  WriteFile
//
//  Created by kai.shang on 16/8/31.
//  Copyright © 2016年 SK. All rights reserved.
//

#include "LibWriteFile.h"
#include "Log.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <dlfcn.h>

string g_logFileName;

using namespace std;
#ifdef __cplusplus
extern "C"
{
#endif
    
    typedef void* Handle;
    typedef int (*FileWriterWrite)(void* WriterHandle, const void* pBuffer,int BufferSize);
    typedef Handle (*CreateFileWriter)(const char* FileName);
    
    void TryLibPath(char *LibPath, char *fileName)
    {
        g_logFileName = fileName;
        g_logFileName += "log";
        cout<<"fileName "<<g_logFileName<<endl;
        PrintLog("come in");
        
        string datasetSoPath = LibPath;
        datasetSoPath += "libDataSetFileOperator.so";
        
        cout<<"so path:"<<datasetSoPath<<endl;
        string str = "so path :"+ datasetSoPath;
        PrintLog(str.c_str());
        
        Handle Libhandle = dlopen(datasetSoPath.c_str(), RTLD_LAZY|RTLD_GLOBAL);
        
        if (Libhandle) {
            CreateFileWriter createFileWriter = (CreateFileWriter)dlsym(Libhandle, "CreateFileWriter");
            FileWriterWrite fileWriterWrite = (FileWriterWrite)dlsym(Libhandle, "FileWriterWrite");
            
            if (createFileWriter && fileWriterWrite) {
                Handle writeHandle = createFileWriter(fileName);
                
                if (writeHandle) {
                    char buf[64]="1111";
                    int size = fileWriterWrite(writeHandle, buf, 64);
                    cout<<"write character"<<size<<endl;
                    
                    str = "write character";
                    PrintLog(str.c_str());
                }else{
                    cout<<"writeHandle is null"<<endl;
                    str = "writeHandle is null";
                    PrintLog(str.c_str());
                }
               
            }
            else{
                cout<<"dlsym failure"<<endl;
                str = "lsym failure";
                PrintLog(str.c_str());
            }
           
        }
        else{
            cout<<"dlopen failure"<<endl;
            str = "dlopen failure";
          
            PrintLog( dlerror());
        }
    }
    
    
    int  WriteFile(char *filename)
    {
    g_logFileName = filename;
    g_logFileName += "log";
    cout<<"fileName "<<g_logFileName<<endl;
    string str = "Input file name:";
    str += filename;
    PrintLog(str.c_str());
        
 
    
    ofstream fout(filename, std::ios::binary);
    if(!fout){
        PrintLog("fout Error");
    }
    
    char buf[64]="1111";
    fout.write(buf, 64);
    fout.close();
    
    PrintLog("WriteFile Finish");
    return 0;
    }
    
#ifdef __cplusplus
}
#endif