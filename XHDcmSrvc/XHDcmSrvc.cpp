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
#include "PubFunc.h"

using namespace std;
using namespace LOGGER;
using namespace ADO;
CLogger Logger;
CADOSQL Sql;
STORESCPCALLBACK TmpScpFunc;
ConfigFile ConfigInfo;
//����SCP����Ļص�����
void  ManageDCM(TStoreProgress* progress, TDcmInfoHeader* DcmInfoHeader)
{
	return;
}
//����������յ���DCM�ļ��߳�
DWORD WINAPI AnalyseDcmFileThread(LPVOID lpParameter)
{
	string DstFolderPath = ConfigInfo.GetDcmOutputPath();
	vector<string> DstFileVec;
	while (true)
	{
		DstFileVec.clear();
		if (!getDstFiles(DstFolderPath, "\\*.dcm", DstFileVec,true))
		{
			Sleep(200);//���û���µ�dcm�ļ���û200����ɨ��һ��
			continue;
		}
		for (vector<string>::iterator TmpItr = DstFileVec.begin();TmpItr != DstFileVec.end();TmpItr++)
		{
			string CurDcmFileName = *TmpItr;
			string CurDcmFilePath = DstFolderPath + "\\" + CurDcmFileName;
			TDcmObjManager DcmObjMngr(CurDcmFilePath);
			if (!DcmObjMngr.IsDcmOpenSuccess())//���Dcm�ļ���ʧ�ܣ�ɾ����ǰ�ļ��󣬿�ʼ������һ���ļ�
			{
				Logger.TraceError("Dcm�ļ���ʧ��:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			//��ȡͷ��Ϣ
			TDcmInfoHeader* DcmInfoHeader = DcmObjMngr.GetDcmInfoHeader();
			if (DcmInfoHeader == NULL)
			{
				Logger.TraceError("Dcm�ļ�ͷΪ��:%s", CurDcmFilePath.c_str());
				DeleteFile(LPCWSTR(CurDcmFilePath.c_str()));
				continue;
			}
			if (DcmInfoHeader->SOPInstanceUID == NULL)
			{
				Logger.TraceError("Dcm�ļ�SOPUidΪ��:%s", CurDcmFilePath.c_str());
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
			if (!IsFileExists(PatFolderName))
			{
				CreateDirectory((LPCTSTR)PatFolderName.c_str(),NULL);
			}
		}
	}
	return 1;
}
//��־�����ݿ�ȳ�ʼ��
bool StartInit(string DcmFolderPath)
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