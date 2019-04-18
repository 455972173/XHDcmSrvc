//����.opt���������Ϣ
#ifndef _OPTFILEDEF_H_
#define _OPTFILEDEF_H_
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include "Ini.h"
#include "Logger.h"
using namespace std;
using namespace LOGGER;
struct OptPara
{
	string SerialNoStr;       //24b ��������к�
	string SupervisorPwd;     //16b
	string EquipSeriesNo;     //8b  �豸�������
	bool   IsSOPInstUIDFileName;//1b  �� SOP Instance UID ���������ļ����е�DICOM�ļ�
	bool   IsSerialNoLegal;     //1b  ���������кŵĺϷ���
};
class OptConfigFile
{
public:
	OptConfigFile();
	~OptConfigFile();
	bool ReadConfigFile(string ConfigFilePath);
	string GetSerialNoStr()
	{
		return m_IniConfig.ReadString("OptPara", "SerialNoStr", "");
	}
	string GetSupervisorPwd()
	{
		return m_IniConfig.ReadString("OptPara", "SupervisorPwd", "");
	}
	string GetEquipSeriesNo()
	{
		return m_IniConfig.ReadString("OptPara", "EquipSeriesNo", "");
	}
	bool GetIsSOPInstUIDFileName()
	{
		if (_stricmp(m_IniConfig.ReadString("OptPara", "SOPInstUIDFileName", "").c_str(), "true"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GetIsCheckSerialNo()
	{
		if (_stricmp(m_IniConfig.ReadString("OptPara", "CheckSerialNo", "").c_str(), "true"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	CIni m_IniConfig;
	OptPara m_optPara;
	string m_ConfigFilePath;
};
#endif // !_OPTFILEDEF_H_

