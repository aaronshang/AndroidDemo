//
//  com_example_test_CreateFile.cpp
//  WriteFile
//
//  Created by kai.shang on 16/8/31.
//  Copyright © 2016年 SK. All rights reserved.
//

#include <stdio.h>
#include "com_example_test_CreateFile.h"
#include "LibWriteFile.h"

JNIEXPORT void JNICALL Java_com_example_test_CreateFile_createFile
(JNIEnv * env, jobject jobj, jstring jFileName)
{
    char *filename = (char*) env->GetStringUTFChars(jFileName, NULL);
    WriteFile(filename);
    env->ReleaseStringUTFChars(jFileName, filename);
}

JNIEXPORT void JNICALL Java_com_example_test_CreateFile_initLibPath
(JNIEnv * env, jobject jobj, jstring jFileName, jstring jLibPath){
    char *libPath = (char*) env->GetStringUTFChars(jLibPath, NULL);
    char *filename = (char*) env->GetStringUTFChars(jFileName, NULL);
    TryLibPath(libPath, filename);
    env->ReleaseStringUTFChars(jLibPath, libPath);
    env->ReleaseStringUTFChars(jFileName, filename);
}