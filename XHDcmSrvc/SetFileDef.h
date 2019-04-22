//����XHDcmGate.set���������Ϣ
#pragma once
#ifndef _SETFILEDEF_H_
#define _SETFILEDEF_H_
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include "Ini.h"
#include "Logger.h"
using namespace std;
using namespace LOGGER;
#define SetupFileExtName '.set';
#define SetupFileFlag  'XHDCMSET'; //���ݳ�����������޸�(������10���ַ�)
#define MinSetupFileVersion  1;
#define MaxSetupFileVersion  1;
#define MaxLineLength 1024;
extern CLogger Logger;
//TDBServerType ���ݿ����������
enum TDBServerType
{
	dsLocal = 0, //�������ݿ������
	dsRemote //Զ�����ݿ������
};

struct ConfigHead
{
	string m_FileFlag;//XHDCMSET
	string m_Version;//�汾��
	string m_EncryptKey;//key�ǵ�ǰ�ľ�������
	string m_SaveDateTime;//��ǰ����
};
struct ConfigPara
{
	//���ݿ����
	TDBServerType m_DBServerType;//���ݿ����������
	string m_HostIPAdress;//���ݿ������IP��ַ
	string m_DBFileName;//���ݿ��ļ���
	string m_IBServerPath;//ibserver.exe��ȫ·����
	string m_DBBkUpFileName;//���ݿⱸ���ļ���
	//DICOM����������
	string m_DcmAppEntity;//DICOM������AE
	int m_DcmServerPort;//DICOM�������˿ں�
	string m_DcmOutputPath;//����DICOM�ļ����ļ�����
	bool m_IsAutoStartDcmServer;//�Ƿ��Զ�����DICOM������
	bool m_IsAutoConnectDatabase;//�Ƿ��Զ��������ݿ��ļ�
	int m_MaxPDULength;
	//����
	int m_IBServerStartDelay;//ibserver.exe������Ҫ��ʱ��(s) �����ã�
	bool m_IsSOPInstUIDFileName;//�Ƿ��� SOP Instance UID ���������ļ����е�DICOM�ļ������ã�
	bool m_IsOverridePreDCMFile;//�Ƿ����ļ����� SOP Instance UID ��Ӧ��DICOM�ļ�����ʱ���ú��յ����ļ����串��
	string m_EquipSeriesNo;//�豸�������
	int m_MaxDBConnectTimes;//���ݿ���������������ԵĴ���
	bool m_IsSepDcmMLOutputPath;//�Ƿ��õ������ļ��б�������ͼ���ļ�
	string m_DcmMLOutputPath;//��������ͼ���ļ����ļ�����
};

class ConfigFile
{
public:
	ConfigFile() {}
	~ConfigFile() {}
	bool ReadConfigFile(string ConfigFilePath);
	string GetFileFlag()
	{
		return m_IniConfig.ReadString("ConfigHead", "FileFlag", "");
	}
	string GetDcmOutputPath()
	{
		return m_IniConfig.ReadString("ConfigInfo","DICOMFilePath","");
	}
	string GetServerIp()
	{
		return m_IniConfig.ReadString("ConfigInfo", "ServerIp", "127.0.0.1");
	}
	string GetServerPort()
	{
		return m_IniConfig.ReadString("ConfigInfo", "ServerPort", "");
	}
	string GetMaxPdu()
	{
		return m_IniConfig.ReadString("ConfigInfo", "MaxPdu", "");
	}
	bool GetIsSepDcmMLOutputPath()
	{
		if (_stricmp(m_IniConfig.ReadString("ConfigInfo", "IsUseSingleDICOMFolder", "").c_str(), "true"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GetIsOverridePreDCMFile()
	{
		if (_stricmp(m_IniConfig.ReadString("ConfigInfo", "IsOverridePreDICOMFile", "").c_str(), "true"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string GetDcmMLOutputPath()
	{
		return m_IniConfig.ReadString("ConfigInfo", "PicFilePath", "");
	}
	string GetEquipSeriesNo()
	{
		return m_IniConfig.ReadString("ConfigInfo", "DeviceSN", "");
	}
	string GetDBFileName()
	{
		return m_IniConfig.ReadString("ConfigInfo", "DBFileName", "");
	}


private:
	ConfigHead m_ConfigHead;
	ConfigPara m_ConfigPara;
	CIni m_IniConfig;
	string m_ConfigFilePath;
};

#endif // ! _SETFILEDEF_H_
