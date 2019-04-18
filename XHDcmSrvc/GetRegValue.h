//��ȡע�����Ϣ
#ifndef __GETREGVALUE_H__
#define __GETREGVALUE_H__

#include <string>
#include <stdlib.h>
using namespace std;
//---------------------------------------------------------------
//function: 
//          GetRegValue ��ȡע�����ָ������ֵ
//Access:
//           public  
//Parameter:
//          [in] HKEY KeyType - ע���������ͣ�����Ĳ���ֻ������������ֵ��
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
//          [in] const std::string & strUrl - Ҫ���� �ļ���·��
//          [in] const std::string & strKey - ָ���ļ�
//Returns:
//          std::string - ָ������ֵ
//Remarks:
//          ...
//author:   luoweifu
//---------------------------------------------------------------
std::string GetRegValue(HKEY nKeyType, const std::string& strUrl, const std::string& strKey);

//����ֲ�汾 wstring => string
std::string ws2s(const std::wstring& ws);

//����ֲ�汾 string => wstring
std::wstring s2ws(const std::string& s);


#endif  //__GETREGVALUE_H__
