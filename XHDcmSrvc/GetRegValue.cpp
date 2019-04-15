#include "stdafx.h"
#include <Windows.h>
#include "GetRegValue.h"

//����ֲ�汾 wstring => string
std::string ws2s(const std::wstring& wstr)
{
	string result;
	//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}

//����ֲ�汾 string => wstring
std::wstring s2ws(const std::string& str)
{
	wstring result;
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ��� 
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';//����ַ�����β  
	result.append(buffer);//ɾ��������������ֵ
	delete[] buffer;
	return result;
}

std::string GetRegValue(HKEY KeyType, const std::string& strUrl, const std::string& strKey)
{
	std::string strValue("");
	HKEY  hKeyResult = NULL;
	DWORD dwSize = 0;
	DWORD dwDataType = 0;
	std::wstring wstrUrl = s2ws(strUrl);
	std::wstring wstrKey = s2ws(strKey); 

	//��ע���
	if (ERROR_SUCCESS == ::RegOpenKeyEx(KeyType, wstrUrl.c_str(), 0, KEY_QUERY_VALUE, &hKeyResult))
	{
		// ��ȡ����ĳ���dwSize������dwDataType
		::RegQueryValueEx(hKeyResult, wstrKey.c_str(), 0, &dwDataType, NULL, &dwSize);
		switch (dwDataType)
		{
		case REG_MULTI_SZ:
		{
			//�����ڴ��С
			BYTE* lpValue = new BYTE[dwSize];
			//��ȡע�����ָ���ļ�����Ӧ��ֵ
			LONG lRet = ::RegQueryValueEx(hKeyResult, wstrKey.c_str(), 0, &dwDataType, lpValue, &dwSize);
			delete[] lpValue;
			break;
		}
		case REG_SZ:
		{
			//�����ڴ��С
			wchar_t* lpValue = new wchar_t[dwSize];
			memset(lpValue, 0, dwSize * sizeof(wchar_t));
			//��ȡע�����ָ���ļ�����Ӧ��ֵ
			if (ERROR_SUCCESS == ::RegQueryValueEx(hKeyResult, wstrKey.c_str(), 0, &dwDataType, (LPBYTE)lpValue, &dwSize))
			{
				std::wstring wstrValue(lpValue);
				strValue = ws2s(wstrValue);
			}
			delete[] lpValue;
			break;
		}
		default:
			break;
		}
	}

	//�ر�ע���
	::RegCloseKey(hKeyResult);


	return strValue;
}