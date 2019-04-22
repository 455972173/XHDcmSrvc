#include "stdafx.h"
#include <Windows.h>
#include "GetRegValue.h"
#include <comutil.h> 
#include "PubFunc.h"

//可移植版本 wstring => string
std::string ws2s(const std::wstring& wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//可移植版本 string => wstring
std::wstring s2ws(const std::string& str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), (LPWSTR)buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
									//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

std::string GetRegValue(HKEY KeyType, const std::string& strUrl, const std::string& strKey)
{
	std::string strValue("");
	HKEY  hKeyResult = NULL;
	DWORD dwSize = 0;
	DWORD dwDataType = 0;
	std::wstring wstrUrl = AnsiToUNICODE(strUrl);
	std::wstring wstrKey = AnsiToUNICODE(strKey);

	LSTATUS RetStatus = ::RegOpenKeyEx(KeyType, (LPCWSTR)wstrUrl.c_str(), 0, KEY_QUERY_VALUE, &hKeyResult);
	//打开注册表
	if (RetStatus == ERROR_SUCCESS)
	{
		// 获取缓存的长度dwSize及类型dwDataType
		::RegQueryValueEx(hKeyResult, (LPCWSTR)wstrKey.c_str(), 0, &dwDataType, NULL, &dwSize);
		switch (dwDataType)
		{
		case REG_MULTI_SZ:
		{
			//分配内存大小
			BYTE* lpValue = new BYTE[dwSize];
			//获取注册表中指定的键所对应的值
			LONG lRet = ::RegQueryValueEx(hKeyResult, (LPCWSTR)wstrKey.c_str(), 0, &dwDataType, lpValue, &dwSize);
			delete[] lpValue;
			break;
		}
		case REG_SZ:
		{
			//分配内存大小
			wchar_t* lpValue = new wchar_t[dwSize];
			memset(lpValue, 0, dwSize * sizeof(wchar_t));
			//获取注册表中指定的键所对应的值
			if (ERROR_SUCCESS == ::RegQueryValueEx(hKeyResult, (LPCWSTR)wstrKey.c_str(), 0, &dwDataType, (LPBYTE)lpValue, &dwSize))
			{
				std::wstring wstrValue(lpValue);
				strValue = UnicodeToANSI(wstrValue);
			}
			delete[] lpValue;
			break;
		}
		default:
			break;
		}
	}

	//关闭注册表
	::RegCloseKey(hKeyResult);


	return strValue;
}