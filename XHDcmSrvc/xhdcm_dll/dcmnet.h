#pragma once

#include "dcmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

	//ec - error code 函数调用返回代码
	//用于XHDCM_EchoSCURun, XHDCM_StoreSCURun, XHDCM_PrintSCURun
#define ecNormal                       0
#define ecOtherError                   1
#define ecInvalidServerName            2
#define ecInvalidServerPort            3
#define ecInvalidServerTitle           4
#define ecInvalidClientTitle           5
#define ecInvalidMaxPDUSize            6
#define ecFailedToInitNetwork          7
#define ecFailedToInitAsscocParas      8
#define ecFailedToSetAppTitles         9
#define ecFailedToSetTransLayerType    10
#define ecFailedToSetPresentAddrs      11
#define ecFailedToSetPresentContexts   12
	//modified in V1.5.1 begin
	//#define ecFailedToCreateAssociation    13
#define ecAssociationRequestFailed     13
	//modified in V1.5.1 end
#define ecFailedToCountPresentContexts 14
#define ecPeerRequestedRelease         15
#define ecPeerAbortedAssociation       16
#define ecAssociationRejected          17 //added in V1.5.1
	//added in V3.0 begin
#define ecPrintManagementNotSupported  18 
#define ecRequestPrinterSettingFailed  19
#define ecCreateBasicFilmSessionFailed 20
#define ecCreateBasicFilmBoxFailed     21
#define ecSetBasicImageBoxFailed       22
#define ecPrintBasicFilmBoxFailed      23
#define ecSetBasicAnnotationBoxFailed  24
#define ecInvalidFileName              25
#define ecInvalidOutputDirectory       26
	//added in V3.0 end

	//下列部分用于定义dicom结构变量
	typedef enum
	{
		StoreBegin, 					/* before data set */
		StoreProgressing,			/* during data set */
		StoreEnd							/* after data set */
	} TStoreProgressState;

	typedef struct {
		TStoreProgressState state;	/* current state */
		long callbackCount;					/* callback execution count */
		long progressBytes;					/* sent/received so far */
		long totalBytes;				  	/* total/estimated total to send/receive */
	} TStoreProgress;

	typedef struct {
		const char * ServerName;   //Server Name (例: 192.168.16.100)
		long         ServerPort;   //Server Port (例: 104)
		const char * ServerTitle;  //Server AE (例: XHDICOM)
		const char * ClientTitle;  //Client AE 
		long         MaxPDULength; //bytes，取值范围[4096, 131072]
		long         TimeOut;      //s，>=0
	} TDCMAssocPara; //association parameters


#ifdef XHDCM_EXPORTS
#define XHDICOM_API  __declspec(dllexport)
#else
#define XHDICOM_API  __declspec(dllimport)
#endif

	//下列部分用于定义SCU/SCP回调函数
	typedef void(*STORESCUCALLBACK)(TStoreProgress* progress);
	typedef void(*STORESCPCALLBACK)(TStoreProgress* progress, TDcmInfoHeader * DcmInfoHeader);

	//下列函数用于处理 Echo SCU 高级网络服务
	XHDICOM_API long  XHDCM_EchoSCURun(TDCMAssocPara * DCMAssocPara);

	//下列函数用于处理 Store SCU 高级网络服务
	XHDICOM_API long  XHDCM_StoreSCURun(TDCMAssocPara * DCMAssocPara, const char * FileList, STORESCUCALLBACK Callback);

	//下列函数用于处理 Store SCP 高级网络服务
	XHDICOM_API bool  XHDCM_StoreSCPRun(TDCMAssocPara * DCMAssocPara, const char * OutputDir, STORESCPCALLBACK Callback);
	XHDICOM_API bool  XHDCM_StoreSCPTerminate(void);
	XHDICOM_API bool  XHDCM_StoreSCPIsRunning(void);

	//下列函数用于处理 Store SCP 低级网络服务
	XHDICOM_API bool  XHDCM_StoreSCPSetVar(TDCMAssocPara * DCMAssocPara, const char * OutputDir, STORESCPCALLBACK Callback);
	XHDICOM_API bool  XHDCM_StoreSCPInitNet(void);
	XHDICOM_API bool  XHDCM_StoreSCPProcess(void);
	XHDICOM_API bool  XHDCM_StoreSCPDropNet(void);

	//下列函数用于处理 Print SCU 高级网络服务
	XHDICOM_API long  XHDCM_PrintSCURun(TDCMAssocPara * DCMAssocPara, TDcmFilmSession & FilmSession, TDcmFilmBoxIOD & FilmBox); //added in V3.0

	//下列函数用于处理 Find SCU 高级网络服务
	XHDICOM_API long  XHDCM_FindSCURun(TDCMAssocPara * DCMAssocPara, const char * FileName, const char * OutputDir); //added in V3.0

#if defined(__cplusplus)
};
#endif