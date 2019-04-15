// XHDcmSrvc.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <string>
#include <time.h>
#include "windows.h"
#include "Logger.h"
#include "Ini.h"
#include "ADOSQL.h"
#include "DCMObj.h"
#include "GetRegValue.h"
#include "SetFileDef.h"

using namespace std;
using namespace LOGGER;
using namespace ADO;
CLogger Logger;
CADOSQL Sql;
STORESCPCALLBACK TmpScpFunc;
ConfigFile ConfigInfo;
//CIni IniConfig;
//int main(int argc,char* argv[])
//{
//	IniConfig.ReadConfig("E:\\LS\\CTPic\\config.ini");
//	string HostIp   = IniConfig.ReadString("TEST1", "ip", "");
//	string HostPort = IniConfig.ReadString("TEST2", "port", "");
//	string HostName = IniConfig.ReadString("TEST3", "name", "");
//	printf("IP:%s\tPort:%s\tName:%s\r\n", HostIp.c_str(), HostPort.c_str(), HostName.c_str());
//
//	printf("XHDcmSrvc Start\r\n");
//	string OutputDir = "E:\\LS\\CTPic\\ReceiveCTPic";
//	TDCMAssocPara CurDCMAssocPara;
//	CurDCMAssocPara.ServerName = "127.0.0.1";
//	CurDCMAssocPara.ServerPort = 10101;
//	CurDCMAssocPara.ServerTitle = "XHDICOM";
//	CurDCMAssocPara.ClientTitle = "XHDICOM";
//	CurDCMAssocPara.MaxPDULength = 16384;
//	CurDCMAssocPara.TimeOut = 1;
//
//	TmpScpFunc = ManageDCM;
//	bool IsRunSuccess =  XHDCM_StoreSCPRun(&CurDCMAssocPara, OutputDir.c_str(), TmpScpFunc);
//	while (true)
//	{
//		Sleep(1);
//	}
//    return 0;
//}

void  ManageDCM(TStoreProgress* progress, TDcmInfoHeader* DcmInfoHeader)
{
	return;
}
DWORD WINAPI AnalyseDcmFileThread(LPVOID lpParameter)//解析处理接收到的DCM文件线程
{
	return 1;
}
bool StartInit(string DcmFolderPath)//日志、数据库等初始化
{
	//初始化日志存放路径
	Logger.Init(LogLevel_Info, DcmFolderPath + "\\log\\");
	Logger.TraceInfo("-------------XHDcmSrvc程序启动-------------");
	Logger.TraceInfo("当前注册表中的相关配置文件存放路径为 :%s", DcmFolderPath.c_str());

	//初始化配置文件存放路径，读取配置文件
	string ConfigFilePath = DcmFolderPath + "\\XHDcmGate.set";
	if (!ConfigInfo.ReadConfigFile(ConfigFilePath))
	{
		Logger.TraceError("%s打开失败", ConfigFilePath.c_str());
		return false;
	}

	//连接数据库
	Sql.Connect();
	if (!Sql.IsOpen())
	{
		Logger.TraceError("数据库服务器连接失败，程序退出");
		return false;
	}
	else
	{
		Logger.TraceInfo("数据库服务器连接成功");
	}
	TDCMAssocPara CurDCMAssocPara;
	CurDCMAssocPara.ServerName = "127.0.0.1";
	CurDCMAssocPara.ServerPort = 10101;
	CurDCMAssocPara.ServerTitle = "XHDICOM";
	CurDCMAssocPara.ClientTitle = "XHDICOM";
	CurDCMAssocPara.MaxPDULength = 16384;
	CurDCMAssocPara.TimeOut = 1;
	TmpScpFunc = ManageDCM;
	bool IsRunSuccess =  XHDCM_StoreSCPRun(&CurDCMAssocPara, OutputDir.c_str(), TmpScpFunc);
	return true;
}
int main(int argc, char* argv[])
{
	//读取注册表获取相关配置文件存放路径
	string DcmFolderPath = GetRegValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\SHINVA\\XHDICOM", "DcmFolderName");
	if (!StartInit(DcmFolderPath))
	{
		exit(0);
	}

	//启动DCM接收服务
	HANDLE thread = CreateThread(NULL, 0, AnalyseDcmFileThread, NULL, 0, NULL);

	while (true)
	{
		Sleep(500);
	}
	return 1;
}