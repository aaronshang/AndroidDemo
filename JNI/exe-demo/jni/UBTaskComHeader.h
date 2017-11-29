/**********************************************************************
* Copyright (C) 2017 -  - All Rights Reserved
*
* �ļ�����:			UBTaskComHeader.h
* ժ    Ҫ:			���幫���ṹ�弰�ص�����
*
* ��    ��:			shangkai
* ��    ��:
* ˵	����
*
***********************************************************************/

#ifndef UBTASK_HEADER_H_
#define UBTASK_HEADER_H_


//connect type
typedef enum UBConnectionType
{
	UBConnectionType_Current=0,
	UBConnectionType_VirtualNetwork,
	UBConnectionType_PPP,
	UBConnectionType_AT,
	UBConnectionType_NDIS
}UBConnectionType;

//reconnect network PPP
typedef enum UBReconnectNetwork
{
	UBReconnectNetwork_Never,
	UBReconnectNetwork_Everytime,
	UBReconnectNetwork_AfterFinish
}UBReconnectNetwork;

typedef struct UBConnectionPPPConfig
{
	char apn[32];
	char connection_name[64];
	char ppp_number[64];
	char ppp_user[32];
	char ppp_passwd[32];
}UBConnectionPPPConfig;

typedef struct UBConnectionATConfig
{
	char apn[32];
}UBConnectionATConfig;

typedef enum ECycleModeType
{
	ECycleModeTypeInteval = 0,	//Interval,�����Լ��
	ECycleModeTypePeriods		//Period������������
}ECycleModeType;

typedef struct UBTaskAdvConfig
{
	int test_times;
	int interval;
	int cyclePeriod_s;
	int noflow_timeout_s;
	ECycleModeType cycleModel; 
	UBConnectionType connectionType;
	UBReconnectNetwork reconnectWork;
	UBConnectionPPPConfig pppConfig;
	UBConnectionATConfig atConfig;
}UBTaskAdvConfig;


#endif