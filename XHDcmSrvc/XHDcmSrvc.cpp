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
#include "PubFunc.h"
#include "OptFileDef.h"

using namespace std;
using namespace LOGGER;
using namespace ADO;
CLogger Logger;
CADOSQL Sql;////////////////////////////////////////////////////////////////////////////////
STORESCPCALLBACK TmpScpFunc;
ConfigFile ConfigInfo;
OptConfigFile OptInfo;
//启动SCP服务的回调函数
void  ManageDCM(TStoreProgress* progress, TDcmInfoHeader* DcmInfoHeader)
{
	return;
}
//解析处理接收到的DCM文件线程
DWORD WINAPI AnalyseDcmFileThread(LPVOID lpParameter)
{
	string DstFolderPath = ConfigInfo.GetDcmOutputPath();
	vector<string> DstFileVec;
	while (true)
	{
		DstFileVec.clear();
		if (!getDstFiles(DstFolderPath, "\\*.dcm", DstFileVec,true))
		{
			Sleep(200);//如果没有新的dcm文件，没200毫秒扫描一次
			continue;
		}
		for (vector<string>::iterator TmpItr = DstFileVec.begin();TmpItr != DstFileVec.end();TmpItr++)
		{
			string CurDcmFileName = *TmpItr;
			string CurDcmFilePath = DstFolderPath + "\\" + CurDcmFileName;
			TDcmObjManager DcmObjMngr(CurDcmFilePath);
			if (!DcmObjMngr.IsDcmOpenSuccess())//如果Dcm文件打开失败，删除当前文件后，开始解析下一个文件
			{
				Logger.TraceError("Dcm文件打开失败:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			//获取头信息
			TDcmInfoHeader* DcmInfoHeader = DcmObjMngr.GetDcmInfoHeader();
			if (DcmInfoHeader == NULL)
			{
				Logger.TraceError("Dcm文件头为空:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			if (DcmInfoHeader->SOPInstanceUID == NULL)
			{
				Logger.TraceError("Dcm文件SOPUid为空:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			string SOPInstanceUID = DcmInfoHeader->SOPInstanceUID;
			string PatientID;
			string PatientName;
			if (DcmInfoHeader->PatientID == NULL)
			{
				PatientID = "_";
			}
			else
			{
				PatientID = DcmInfoHeader->PatientID;
			}
			if (DcmInfoHeader->PatientName == NULL)
			{
				PatientName = "_";
			}
			else
			{
				PatientName = DcmInfoHeader->PatientName;
			}
			int DotPos = CurDcmFileName.find('.');
			string FileLeadStr = CurDcmFileName.substr(0, DotPos);
			string PatFolderName;
			string DcmOutputPath;
			if ((FileLeadStr == "CT") && (ConfigInfo.GetIsSepDcmMLOutputPath()))
			{
				DcmOutputPath = ConfigInfo.GetDcmMLOutputPath();
			}
			else
			{
				DcmOutputPath = ConfigInfo.GetDcmOutputPath();
				PatFolderName = DcmOutputPath + "\\" + CanvertToValidFileName(PatientID + ' ' + PatientName);
			}
			if (!IsFileExists(PatFolderName) && (DcmOutputPath.length > 0))
			{
				CreateDirectory((LPCTSTR)PatFolderName.c_str(),NULL);
			}
			PatientID = DcmInfoHeader->PatientID;
			if (FileLeadStr != "CT")
			{

			}
		}
	}
	return 1;
}
//日志、数据库初始化 开启Dcm接收服务
bool StartInit(string DcmFolderPath)
{
	//初始化日志存放路径
	Logger.Init(LogLevel_Info, DcmFolderPath + "\\log\\");
	Logger.TraceInfo("-------------XHDcmSrvc程序启动-------------");
	Logger.TraceInfo("当前注册表中的相关配置文件存放路径为 :%s", DcmFolderPath.c_str());

	//初始化.set文件存放路径，读取.set配置文件
	string ConfigFilePath = DcmFolderPath + "\\XHDcmGate.set";
	if (!ConfigInfo.ReadConfigFile(ConfigFilePath))
	{
		Logger.TraceError("%s打开失败", ConfigFilePath.c_str());
		return false;
	}
	//初始化.opt文件存放路径，读取.opt配置文件
	string OptFilePath = DcmFolderPath + "\\" + ConfigInfo.GetEquipSeriesNo() + ".opt";
	if (!OptInfo.ReadConfigFile(OptFilePath))
	{
		Logger.TraceError("%s打开失败", OptFilePath.c_str());
		return false;
	}

	TDCMAssocPara CurDCMAssocPara;
	CurDCMAssocPara.ServerName = ConfigInfo.GetServerIp().c_str();
	CurDCMAssocPara.ServerPort = atoi(ConfigInfo.GetServerPort().c_str());
	CurDCMAssocPara.ServerTitle = "XHDICOM";
	CurDCMAssocPara.ClientTitle = "XHDICOM";
	CurDCMAssocPara.MaxPDULength = atoi(ConfigInfo.GetMaxPdu().c_str());;
	CurDCMAssocPara.TimeOut = 1;
	TmpScpFunc = ManageDCM;
	bool IsRunSuccess =  XHDCM_StoreSCPRun(&CurDCMAssocPara, ConfigInfo.GetDcmOutputPath().c_str(), TmpScpFunc);
	return IsRunSuccess;
}

int main(int argc, char* argv[])
{
	//读取注册表获取相关配置文件存放路径
	string DcmFolderPath = GetRegValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\SHINVA\\XHDICOM", "DcmFolderName");
	//配置文件、日志文件初始化，连接数据库，开始Dcm接收服务
	if (!StartInit(DcmFolderPath))
	{
		exit(0);
	}
	//启动DCM文件处理线程
	HANDLE thread = CreateThread(NULL, 0, AnalyseDcmFileThread, NULL, 0, NULL);
	while (true)
	{
		Sleep(500);
	}
	return 1;
}