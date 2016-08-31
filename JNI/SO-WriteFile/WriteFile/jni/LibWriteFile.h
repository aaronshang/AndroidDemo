//
//  LibWriteFile.hpp
//  WriteFile
//
//  Created by kai.shang on 16/8/31.
//  Copyright © 2016年 SK. All rights reserved.
//

#ifndef LibWriteFile_hpp
#define LibWriteFile_hpp

#include <stdio.h>

#define STAT_API __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

    STAT_API int  WriteFile(char *filename);
    STAT_API void TryLibPath(char *LibPath, char *fileName);
    
#ifdef __cplusplus
}
#endif
    
#endif /* LibWriteFile_hpp */
