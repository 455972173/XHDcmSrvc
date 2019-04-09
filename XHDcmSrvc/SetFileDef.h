//保存XHDcmGate.set相关配置信息
#pragma once
#ifndef _SETFILEDEF_H_
#define _SETFILEDEF_H_
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#define SetupFileExtName '.set';
#define SetupFileFlag  'XHDCMSET'; //根据程序情况加以修改(不超过10个字符)

#define MinSetupFileVersion  1;
#define MaxSetupFileVersion  1;
#define MaxLineLength 1024;
using namespace std;
//TDBServerType 数据库服务器类型
enum TDBServerType
{
	dsLocal = 0, //本地数据库服务器
	dsRemote //远程数据库服务器
};

struct ConfigHead
{
	string m_FileFlag;//XHDCMSET
	string m_Version;//版本号
	string m_EncryptKey;//key是当前的绝对秒数
	string m_SaveDateTime;//当前日期
};
struct ConfigPara
{
	//数据库参数
	TDBServerType m_DBServerType;//数据库服务器类型
	string m_HostIPAdress;//数据库服务器IP地址
	string m_DBFileName;//数据库文件名
	string m_IBServerPath;//ibserver.exe完全路径名
	string m_DBBkUpFileName;//数据库备份文件名
	//DICOM服务器参数
	string m_DcmAppEntity;//DICOM服务器AE
	int m_DcmServerPort;//DICOM服务器端口号
	string m_DcmOutputPath;//保存DICOM文件的文件夹名
	bool m_IsAutoStartDcmServer;//是否自动启动DICOM服务器
	bool m_IsAutoConnectDatabase;//是否自动连接数据库文件
	int m_MaxPDULength;
	//其他
	int m_IBServerStartDelay;//ibserver.exe启动需要的时间(s) （不用）
	bool m_IsSOPInstUIDFileName;//是否用 SOP Instance UID 命名患者文件夹中的DICOM文件（不用）
	bool m_IsOverridePreDCMFile;//是否患者文件夹中 SOP Instance UID 对应的DICOM文件存在时，用后收到的文件将其覆盖
	string m_EquipSeriesNo;//设备出厂编号
	int m_MaxDBConnectTimes;//数据库连接最多允许重试的次数
	bool m_IsSepDcmMLOutputPath;//是否用单独的文件夹保存多层面图像文件
	string m_DcmMLOutputPath;//保存多层面图像文件的文件夹名
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
