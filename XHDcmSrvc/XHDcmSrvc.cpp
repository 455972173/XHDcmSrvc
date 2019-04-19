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
#include "MainDM.h"

using namespace std;
using namespace LOGGER;
using namespace ADO;
CLogger Logger;
STORESCPCALLBACK TmpScpFunc;
ConfigFile ConfigInfo;
OptConfigFile OptInfo;
MainDataModify MainDatMod;
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
			Sleep(200);//如果没有新的dcm文件，每200毫秒扫描一次
			continue;
		}
		for (vector<string>::iterator TmpItr = DstFileVec.begin();TmpItr != DstFileVec.end();TmpItr++)
		{
			string CurDcmFileName = *TmpItr;
			string CurDcmFilePath = DstFolderPath + "\\" + CurDcmFileName;
			TDcmObjManager DcmObjMngr(CurDcmFilePath);
			if (!DcmObjMngr.IsDcmOpenSuccess())//如果Dcm文件打开失败，删除当前文件后，开始解析下一个文件
			{
				SetFileAttributes((LPCWSTR)CurDcmFilePath.c_str(),FILE_ATTRIBUTE_READONLY);
				Logger.TraceError("Dcm文件打开失败:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			//获取头信息
			TDcmInfoHeader* DcmInfoHeader = DcmObjMngr.GetDcmInfoHeader();
			if (DcmInfoHeader == NULL)
			{
				SetFileAttributes((LPCWSTR)CurDcmFilePath.c_str(), FILE_ATTRIBUTE_READONLY);
				Logger.TraceError("Dcm文件头为空:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			if (DcmInfoHeader->SOPInstanceUID == NULL)
			{
				SetFileAttributes((LPCWSTR)CurDcmFilePath.c_str(), FILE_ATTRIBUTE_READONLY);
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
			if (!IsFileExists(PatFolderName) && (DcmOutputPath.length()> 0))
			{
				CreateDirectory((LPCTSTR)PatFolderName.c_str(),NULL);
			}
			PatientID = DcmInfoHeader->PatientID;
			string SOPFileName;
			string FullSOPFileName;
			if (FileLeadStr != "CT")
			{
				if (MainDatMod.DcmSOPFound(PatientID, SOPInstanceUID, SOPFileName))
				{
					FullSOPFileName = PatFolderName + "\\" + SOPFileName;
					if (IsFileExists(FullSOPFileName))
					{
						if (!ConfigInfo.GetIsOverridePreDCMFile())
						{
							DeleteFile((LPCWSTR)CurDcmFilePath.c_str());
							Logger.TraceInfo("File Already Exist 1,Delete :%s", CurDcmFileName.c_str());
							continue;
						}
						DeleteFile((LPCWSTR)FullSOPFileName.c_str());
					}
				}
			}
			if (OptInfo.GetIsSOPInstUIDFileName())
			{
				FullSOPFileName = PatFolderName + "\\" + FileLeadStr + SOPInstanceUID + ".dcm";
			}
			else
			{
				FullSOPFileName = PatFolderName + "\\" + CurDcmFileName;
			}
			if (FileLeadStr != "CT")
			{
				try
				{
					if (!MainDatMod.SaveDicomInfo(*DcmInfoHeader, ExtractFileName(FullSOPFileName)))
					{
						Logger.TraceInfo("File Name :%s,PatientId :%s,PatientName :%s", CurDcmFileName.c_str(), PatientID.c_str(), PatientName.c_str());
						Logger.TraceInfo("%s : rejected by db for conflicted PatientID", CurDcmFileName.c_str());
					}
				}
				catch(exception& e)
				{
					Logger.TraceInfo("File Name :%s,PatientId :%s,PatientName :%s", CurDcmFileName.c_str(), PatientID.c_str(), PatientName.c_str());
					Logger.TraceInfo("%s :write to db error :%s", CurDcmFileName.c_str());
				}
			}
			else
			{
				if (OptInfo.GetIsSOPInstUIDFileName())
				{
					if (IsFileExists(FullSOPFileName))
					{
						if (!ConfigInfo.GetIsOverridePreDCMFile())
						{
							DeleteFile((LPCWSTR)CurDcmFilePath.c_str());
							Logger.TraceInfo("File Already Exist 2,Delete :%s", CurDcmFileName.c_str());
							continue;
						}
						DeleteFile((LPCWSTR)FullSOPFileName.c_str());
					}
				}
			}
			CopyFile((LPCWSTR)CurDcmFilePath.c_str(), (LPCWSTR)FullSOPFileName.c_str(), false);
			if (IsFileExists(FullSOPFileName))
			{
				SetFileAttributes((LPCWSTR)CurDcmFilePath.c_str(), FILE_ATTRIBUTE_HIDDEN);
				Logger.TraceInfo("FullSOPFileName Exist :%s", FullSOPFileName.c_str());
			}
			else
			{
				SetFileAttributes((LPCWSTR)CurDcmFilePath.c_str(), FILE_ATTRIBUTE_READONLY);
				Logger.TraceInfo("FullSOPFileName File Copy Error :%s", FullSOPFileName.c_str());
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
	//连接数据库
	if (!MainDatMod.ConnectDataBase("127.0.0.1", "sa", "123456", "PracticeTest"))
	{
		Logger.TraceError("数据库服务器连接失败，程序退出");
		return false;
	}
	else
	{
		Logger.TraceInfo("数据库服务器连接成功");
	}
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

	//启动DcmServer监听接收文件服务
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