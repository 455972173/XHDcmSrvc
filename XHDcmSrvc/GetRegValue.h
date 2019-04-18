//获取注册表信息
#ifndef __GETREGVALUE_H__
#define __GETREGVALUE_H__

#include <string>
#include <stdlib.h>
using namespace std;
//---------------------------------------------------------------
//function: 
//          GetRegValue 获取注册表中指定键的值
//Access:
//           public  
//Parameter:
//          [in] HKEY KeyType - 注册表项的类型，传入的参数只可能是以下数值：
//			HKEY_CLASSES_ROOT
//			HKEY_CURRENT_USER
//			HKEY_LOCAL_MACHINE
//			HKEY_USERS
//			HKEY_PERFORMANCE_DATA
//			HKEY_CURRENT_CONFIG
//			HKEY_DYN_DATA
//			HKEY_CURRENT_USER_LOCAL_SETTINGS
//			HKEY_PERFORMANCE_TEXT
//			HKEY_PERFORMANCE_NLSTEXT
//          [in] const std::string & strUrl - 要查找 的键的路径
//          [in] const std::string & strKey - 指定的键
//Returns:
//          std::string - 指定键的值
//Remarks:
//          ...
//author:   luoweifu
//---------------------------------------------------------------
std::string GetRegValue(HKEY nKeyType, const std::string& strUrl, const std::string& strKey);

//可移植版本 wstring => string
std::string ws2s(const std::wstring& ws);

//可移植版本 string => wstring
std::wstring s2ws(const std::string& s);


#endif  //__GETREGVALUE_H__
