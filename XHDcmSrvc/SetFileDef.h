//����XHDcmGate.set���������Ϣ
#pragma once
#ifndef _SETFILEDEF_H_
#define _SETFILEDEF_H_
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#define SetupFileExtName '.set';
#define SetupFileFlag  'XHDCMSET'; //���ݳ�����������޸�(������10���ַ�)

#define MinSetupFileVersion  1;
#define MaxSetupFileVersion  1;
#define MaxLineLength 1024;
using namespace std;
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
	ConfigFile(string ConfigFilePath);
	~ConfigFile();
	bool ReadConfigFile();

private:
	ConfigPara m_ConfigPara;
	string m_ConfigFilePath;

};
ConfigFile::ConfigFile(string SetupFilePath)
{
	m_ConfigFilePath = SetupFilePath;
}

#endif // ! _SETFILEDEF_H_
