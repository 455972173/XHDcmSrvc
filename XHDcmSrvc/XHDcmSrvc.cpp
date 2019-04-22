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
			Sleep(200);//���û���µ�dcm�ļ���ÿ200����ɨ��һ��
			continue;
		}
		for (vector<string>::iterator TmpItr = DstFileVec.begin();TmpItr != DstFileVec.end();TmpItr++)
		{
			string CurDcmFileName = *TmpItr;
			string CurDcmFilePath = DstFolderPath + "\\" + CurDcmFileName;
			TDcmObjManager DcmObjMngr(CurDcmFilePath);
			if (!DcmObjMngr.IsDcmOpenSuccess())//���Dcm�ļ���ʧ�ܣ�ɾ����ǰ�ļ��󣬿�ʼ������һ���ļ�
			{
				SetDstFileAttributes(CurDcmFilePath,FILE_ATTRIBUTE_READONLY);
				Logger.TraceError("Dcm�ļ���ʧ��:%s", CurDcmFilePath.c_str());
				DeleteDstFile(CurDcmFilePath);
				continue;
			}
			//��ȡͷ��Ϣ
			TDcmInfoHeader* DcmInfoHeader = DcmObjMngr.GetDcmInfoHeader();
			if (DcmInfoHeader == NULL)
			{
				SetDstFileAttributes(CurDcmFilePath, FILE_ATTRIBUTE_READONLY);
				Logger.TraceError("Dcm�ļ�ͷΪ��:%s", CurDcmFilePath.c_str());
				DeleteDstFile(CurDcmFilePath);
				continue;
			}
			if (DcmInfoHeader->SOPInstanceUID == NULL)
			{
				SetDstFileAttributes(CurDcmFilePath, FILE_ATTRIBUTE_READONLY);
				Logger.TraceError("Dcm�ļ�SOPUidΪ��:%s", CurDcmFilePath.c_str());
				DeleteDstFile(CurDcmFilePath);
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
			}
			PatFolderName = DcmOutputPath + "\\" + CanvertToValidFileName(PatientID + ' ' + PatientName);
			if (!IsFileExists(PatFolderName) && (DcmOutputPath.length()> 0))
			{
				RecursiveDirectory(AnsiToUNICODE(PatFolderName).c_str());
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
							DeleteDstFile(CurDcmFilePath);
							Logger.TraceInfo("File Already Exist 1,Delete :%s", CurDcmFileName.c_str());
							continue;
						}
						DeleteDstFile(FullSOPFileName);
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
							DeleteDstFile(CurDcmFilePath);
							Logger.TraceInfo("File Already Exist 2,Delete :%s", CurDcmFileName.c_str());
							continue;
						}
						DeleteDstFile(FullSOPFileName);
					}
				}
			}
			CopyDstFile(CurDcmFilePath,FullSOPFileName);
			if (IsFileExists(FullSOPFileName))
			{
				SetDstFileAttributes(CurDcmFilePath, FILE_ATTRIBUTE_HIDDEN);
				Logger.TraceInfo("FullSOPFileName Exist :%s", FullSOPFileName.c_str());
				DeleteDstFile(CurDcmFilePath);
			}
			else
			{
				SetDstFileAttributes(CurDcmFilePath, FILE_ATTRIBUTE_READONLY);
				Logger.TraceInfo("FullSOPFileName File Copy Error :%s", FullSOPFileName.c_str());
			}
		}
	}
	return 1;
}
//��־�����ݿ��ʼ�� ����Dcm���շ���
bool StartInit(string DcmFolderPath)
{
	//��ʼ����־���·��
	Logger.Init(LogLevel_Info, DcmFolderPath + "\\log\\");
	Logger.TraceInfo("-------------XHDcmSrvc��������-------------");
	Logger.TraceInfo("��ǰע����е���������ļ����·��Ϊ :%s", DcmFolderPath.c_str());

	//��ʼ��.set�ļ����·������ȡ.set�����ļ�
	string ConfigFilePath = DcmFolderPath + "\\XHDcmGate.set";
	if (!ConfigInfo.ReadConfigFile(ConfigFilePath))
	{
		Logger.TraceError("%s��ʧ��", ConfigFilePath.c_str());
		return false;
	}

	//��ʼ��.opt�ļ����·������ȡ.opt�����ļ�
	string OptFilePath = DcmFolderPath + "\\" + ConfigInfo.GetEquipSeriesNo() + ".opt";
	if (!OptInfo.ReadConfigFile(OptFilePath))
	{
		Logger.TraceError("%s��ʧ��", OptFilePath.c_str());
		return false;
	}

	//�������ݿ�
	if (!MainDatMod.ConnectDataBase("127.0.0.1", "sa", "123456", ConfigInfo.GetDBFileName().c_str()))
	{
		Logger.TraceError("���ݿ����������ʧ�ܣ������˳�");
		return false;
	}
	else
	{
		Logger.TraceInfo("���ݿ���������ӳɹ�");
	}

	//����DcmServer���������ļ�����
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
	//�����ļ�����־�ļ���ʼ�����������ݿ⣬��ʼDcm���շ���
	if (!StartInit(DcmFolderPath))
	{
		exit(0);
	}
	//����DCM�ļ������߳�
	HANDLE thread = CreateThread(NULL, 0, AnalyseDcmFileThread, NULL, 0, NULL);
	while (true)
	{
		Sleep(500);
	}
	return 1;
}