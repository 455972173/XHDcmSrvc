// XHDcmSrvc.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "windows.h"
#include "Logger.h"
#include "Ini.h"
#include "ADOSQL.h"
#include <string>
#include <time.h>
#include "xhdcm_dll\dcmnet.h"
#include "xhdcm_dll\dcmtype.h"
#include "xhdcm_dll\xhdicom.h"

using namespace std;
using namespace LOGGER;
using namespace ADO;
CLogger Logger(LogLevel_Info, CLogger::GetAppPathA().append("log\\"));
CADOSQL Sql;
CIni IniConfig;

STORESCPCALLBACK TmpScpFunc;
void  ManageDCM(TStoreProgress* progress, TDcmInfoHeader* DcmInfoHeader)
{
	printf("***Receive New DICOM File***\r\n");
	printf("TStoreProgress:%d -- %l -- %l -- %l\r\n", progress->state, progress->callbackCount, progress->progressBytes, progress->totalBytes);
	printf("DcmInfoHeader PatientId:%s\r\n", DcmInfoHeader->PatientBirthDate);
	return;
}
int main(int argc,char* argv[])
{
	IniConfig.ReadConfig("E:\\LS\\CTPic\\config.ini");
	string HostIp   = IniConfig.ReadString("TEST1", "ip", "");
	string HostPort = IniConfig.ReadString("TEST2", "port", "");
	string HostName = IniConfig.ReadString("TEST3", "name", "");
	printf("IP:%s\tPort:%s\tName:%s\r\n", HostIp.c_str(), HostPort.c_str(), HostName.c_str());

	printf("XHDcmSrvc Start\r\n");
	string OutputDir = "E:\\LS\\CTPic\\ReceiveCTPic";
	TDCMAssocPara CurDCMAssocPara;
	CurDCMAssocPara.ServerName = "127.0.0.1";
	CurDCMAssocPara.ServerPort = 10101;
	CurDCMAssocPara.ServerTitle = "XHDICOM";
	CurDCMAssocPara.ClientTitle = "XHDICOM";
	CurDCMAssocPara.MaxPDULength = 16384;
	CurDCMAssocPara.TimeOut = 1;

	TmpScpFunc = ManageDCM;
	bool IsRunSuccess =  XHDCM_StoreSCPRun(&CurDCMAssocPara, OutputDir.c_str(), TmpScpFunc);
	while (true)
	{
		Sleep(1);
	}
    return 0;
}

