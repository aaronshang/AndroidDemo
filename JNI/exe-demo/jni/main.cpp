#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

#include "FtpDownHeader.h"
#include "UBDLLLoad.h"

typedef void(*ftp_down_qos_callback)(void* user, FtpQoS  qos);
typedef void(*ftp_up_qos_callback)(void* user, FtpQoS  qos);
typedef void(*curl_ubnotify_callback)(void* user, int event, const char* data);

/*��ʼ��FTP�����������ؾ��*/
typedef void*	(*InitFtpDownload)(void*, curl_ubnotify_callback, ftp_down_qos_callback);
typedef void	(*FtpDownConfigTask)(void* user, UBFtpDownConfig config);
typedef int		(*FtpDown_Run)(void*);
typedef void	(*FtpDown_Stop)(void*, EFTPStopType type);
typedef void	(*FtpDown_Close)(void*);

	InitFtpDownload mInitFtpDown;
	FtpDownConfigTask mConfigFunc;
	FtpDown_Run		mRunFunc;
	FtpDown_Stop	mStopFunc;
	FtpDown_Close	mCloseFunc;

static void ftp_event_callback(void* user, int eventType, const char* data)
{
	printf("recv event type:%d\n", eventType);
}

static void FTP_Down_Qos_Output(void* user, FtpQoS qos){
	
	printf("recv %lld\n", qos.now);
}

int main()
{
	cout<<"hello"<<endl;
	string libName = "/data/local/tmp/libUBFtpDown.so";
	
	UBDllLoad *dllHandle = new UBDllLoad();
	dllHandle->Load(libName.c_str());

	mInitFtpDown = (InitFtpDownload)dllHandle->GetSymbol("InitFtpDownload");
	mRunFunc = (FtpDown_Run)dllHandle->GetSymbol("Run");
	mStopFunc = (FtpDown_Stop)dllHandle->GetSymbol("Stop");
	mCloseFunc = (FtpDown_Close)dllHandle->GetSymbol("Close");
	mConfigFunc = (FtpDownConfigTask)dllHandle->GetSymbol("ConfigFtpDown");

	if (mInitFtpDown && mRunFunc && mStopFunc && mCloseFunc && mConfigFunc)
	{
		cout<<"load success"<<endl;
	}else{
		cout<<"load failure"<<endl;
	}


	cout<<"start ftp down"<<endl;
	void* ftpHandle = mInitFtpDown(NULL, ftp_event_callback, FTP_Down_Qos_Output);
	UBFtpDownConfig config;
	memset(&config, 0, sizeof(config));
	strcpy(config.user_name, "HNLT_LTE_GENRL");
	strcpy(config.user_passwd, "Admin@123");
	strcpy(config.sever_ip, "220.202.152.132");
	strcpy(config.server_file_name, "/Download/5M");
	
	config.downSchema = UBDownload_Time;
	config.download_time = 10;
	config.thread_count = 1;
	mConfigFunc(ftpHandle, config);
	int ret = mRunFunc(ftpHandle);
	cout<<"ret:"<<ret<<endl;
	mCloseFunc(ftpHandle);
	
	cout<<"release"<<endl;
	delete dllHandle;

	return 0;
}