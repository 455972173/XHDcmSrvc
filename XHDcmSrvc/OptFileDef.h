//保存.opt相关配置信息
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
	string SerialNoStr;       //24b 软件的序列号
	string SupervisorPwd;     //16b
	string EquipSeriesNo;     //8b  设备出厂编号
	bool   IsSOPInstUIDFileName;//1b  用 SOP Instance UID 命名患者文件夹中的DICOM文件
	bool   IsSerialNoLegal;     //1b  检查软件序列号的合法性
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

