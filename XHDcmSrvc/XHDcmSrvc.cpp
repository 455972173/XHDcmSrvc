// XHDcmSrvc.cpp : �������̨Ӧ�ó������ڵ㡣
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
DWORD WINAPI AnalyseDcmFileThread(LPVOID lpParameter)//����������յ���DCM�ļ��߳�
{
	return 1;
}
bool StartInit(string DcmFolderPath)//��־�����ݿ�ȳ�ʼ��
{
	//��ʼ����־���·��
	Logger.Init(LogLevel_Info, DcmFolderPath + "\\log\\");
	Logger.TraceInfo("-------------XHDcmSrvc��������-------------");
	Logger.TraceInfo("��ǰע����е���������ļ����·��Ϊ :%s", DcmFolderPath.c_str());

	//��ʼ�������ļ����·������ȡ�����ļ�
	string ConfigFilePath = DcmFolderPath + "\\XHDcmGate.set";
	if (!ConfigInfo.ReadConfigFile(ConfigFilePath))
	{
		Logger.TraceError("%s��ʧ��", ConfigFilePath.c_str());
		return false;
	}

	//�������ݿ�
	Sql.Connect();
	if (!Sql.IsOpen())
	{
		Logger.TraceError("���ݿ����������ʧ�ܣ������˳�");
		return false;
	}
	else
	{
		Logger.TraceInfo("���ݿ���������ӳɹ�");
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
	//��ȡע����ȡ��������ļ����·��
	string DcmFolderPath = GetRegValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\SHINVA\\XHDICOM", "DcmFolderName");
	if (!StartInit(DcmFolderPath))
	{
		exit(0);
	}

	//����DCM���շ���
	HANDLE thread = CreateThread(NULL, 0, AnalyseDcmFileThread, NULL, 0, NULL);

	while (true)
	{
		Sleep(500);
	}
	return 1;
}