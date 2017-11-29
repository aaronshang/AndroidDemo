/**********************************************************************
* Copyright (C) 2017 -  - All Rights Reserved
*
* 文件名称:			FtpDownHeader.h
* 摘    要:			定义公共结构体及回调函数
*
* 作    者:			shangkai
* 修    改:
* 说	明：
*
***********************************************************************/

#ifndef FTPDOWN_HEADER_H_
#define FTPDOWN_HEADER_H_

#include "UBTaskComHeader.h"

#include <stdio.h>
typedef void(*curl_ubnotify_callback)(void* user, int event, const char* data);

typedef enum EFTPStopType{
	EFTPStopType_UserStop = 6,
	EFTPStopType_NoFlow = 1,
	EFTPStopType_NoService = 2,
	EFTPStopType_ConnectionLost = 4,
	EFTPStopType_Timeout = 5,

}EFTPStopType;

typedef struct FtpQoS
{
	long long now;
	long long total;
	int timems;
}FtpQoS;

//upload mode
typedef enum UploadSchema
{
	UBUploadSchema_File = 0,
	UBUploadSchema_Time,
	UBUploadSchema_Size
}UploadSchema;

//download mode
typedef enum DownSchema
{
	UBDownload_File,
	UBDownload_Time
}DownSchema;

typedef void(*ftp_down_qos_callback)(void* user, FtpQoS  qos);
typedef void(*ftp_up_qos_callback)(void* user, FtpQoS  qos);

typedef struct UBFtpDownConfig
{
	char sever_ip[32];
	int  sever_port;
	char user_name[64];
	char user_passwd[64];
	char server_file_name[256];
	DownSchema downSchema;

	int thread_count;
	int no_flow_timeout;
	int downloadTimeout;
	int download_time;
	char bind_ip[32];

	//internel read from config
	int tcp_send_buffer_size;
	int tcp_recv_buffer_size;

}UBFtpDownConfig;

typedef struct UBFtpUpConfig
{
	char sever_ip[32];
	int  sever_port;
	char user_name[64];
	char user_passwd[64];
	char server_store_path[128];	//store path
	char server_store_filename[128];

	char up_file_name[256];
	UploadSchema uploadSchema;
	long long fileSize; //Byte

	int thread_count;
	int no_flow_timeout;
	int uploadTimeout;
	int play_time;
	char bind_ip[32];

	//internel read from config
	int tcp_send_buffer_size;
	int tcp_recv_buffer_size;
}UBFtpUpConfig;

typedef struct FtpFile
{
	char *filename;
	FILE *stream;
}FtpFile;

struct callback_data {
	FILE *output;
};

typedef enum UBFtpSessionResult
{
	UBFTP_Session_Result_Success = 1,
	UBFTP_Session_Result_Drop,
	UBFTP_Session_Result_Failure,
	UBFTP_Session_Result_Connect_Failure,
	UBFTP_Session_Result_Login_Failure
}UBFtpSessionResult;

typedef enum UBFTPSessionReason{
	UBFTP_Session_Reason_Normal = 0,
	UBFTP_Session_Reason_NoFlow,
	UBFTP_Session_Reason_NoService,
	UBFTP_Session_Reason_UELost,
	UBFTP_Session_Reason_ConnectionLost,
	UBFTP_Session_Reason_Timeout,
	UBFTP_Session_Reason_UserStop,
	UBFTP_Session_Reason_UnknownError = 10000,
	UBFTP_Session_Reason_NotworkUnavailable = 10001,
	UBFTP_Session_Reason_DestinationHostUnreachable = 10004,
	UBFTP_Session_Reason_TargetFileNotExist = 10006,
	UBFTP_Session_Reason_InvalidUserPasswd = 10008,
	
}UBFTPSessionReason;

#endif