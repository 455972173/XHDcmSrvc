#include "stdafx.h"
#include "PubFunc.h"
#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//找到目的目录下的指定文件，只在mode为*.*的时候支持递归查找所有文件
//IsOnlyName为true的时候得到的vector里面放的都是文件名，为false的时候放的是绝对路径
bool getDstFiles(string path, string mode, vector<string>& files,bool IsOnlyName)
{
	//文件句柄  
	long hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
	p.assign(path).append(mode.c_str());
	if ((hFile = _findfirst(p.c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //比较文件类型是否是文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					p.assign(path).append("\\").append(fileinfo.name);
					if (IsOnlyName)
					{
						files.push_back(fileinfo.name);
					}
					else
					{
						files.push_back(p);
					}
					getDstFiles(p, mode, files);
				}
			}
			else
			{
				p.assign(path).append("\\").append(fileinfo.name);
				if (IsOnlyName)
				{
					files.push_back(fileinfo.name);
				}
				else
				{
					files.push_back(p);
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
	if (files.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//将字符串中的指定字符转换成"_"
string CanvertToValidFileName(string AStr)
{
	string InvalidCharInFileName = "\\/:*?\"<> | ";
	char  FileName[256];
	memset(FileName, 0, 256);
	memcpy(FileName, AStr.c_str(), AStr.size());
	for (int TmpCnt = 0;TmpCnt < AStr.size();TmpCnt++)
	{
		if (InvalidCharInFileName.find(FileName[TmpCnt]) != InvalidCharInFileName.npos)
		{
			FileName[TmpCnt] = '_';
		}
	}
	return FileName;
}
bool IsFileExists(string Path)
{
	if (_access(Path.c_str(), 0) != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Trim(string &s)
{

	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}

}
string GetCurTmStr()
{
	time_t t = time(0);
	tm* CurTm = localtime(&t);
	char TmBuff[64];
	strftime(TmBuff, sizeof(TmBuff), "%Y-%m-%d %H:%M:%S", CurTm); //年-月-日 时-分-秒
	return TmBuff;
}
int CompareNoCase(string str1, string str2)
{
	return _stricmp(str1.c_str(), str2.c_str());
}
string ExtractFileName(string FileName)
{
	int pos = FileName.find_last_of('/');
	string s(FileName.substr(pos + 1));
	return s;
}
std::wstring AnsiToUNICODE(const std::string& str)
{
	wchar_t*  pElementText;
	int    iTextLen;
	// 宽字节转多字节
	iTextLen = MultiByteToWideChar(CP_ACP, 0,
		str.c_str(),
		-1,
		nullptr,
		0);

	pElementText = new wchar_t[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen);

	std::wstring strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
string UnicodeToANSI(const std::wstring& str)
{
	char*  pElementText;
	int    iTextLen;
	// 宽字节转多字节
	iTextLen = WideCharToMultiByte(CP_ACP, 0,
		str.c_str(),
		-1,
		nullptr,
		0,
		nullptr,
		nullptr);

	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		nullptr,
		nullptr);

	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
void __fastcall RecursiveDirectory(wstring wstrDir) // 创建复目录
{
    if (wstrDir.length() <= 3)//是根目录，无需创建目录
    {
        return;
    }
    if (wstrDir[wstrDir.length() - 1] == '\\')   // 将路径改为目录
    {
        wstrDir.erase(wstrDir.end() - 1);
    }
    // 修改文件属性
    WIN32_FIND_DATA wfd;
    HANDLE hFind = FindFirstFile(wstrDir.c_str(), &wfd); // 查找
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FindClose(hFind);
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            return;
    }
    // 创建当前目录的地目录失败
    if (CreateDirectory(wstrDir.c_str(), NULL) == false)
    {// 退到上一级目录
        wstring wstrNewDir = wstrDir;
        while (wstrNewDir[wstrNewDir.length()-1] != '\\')     // 撤到当前目录的上一个目录
        {
            wstrNewDir.erase(wstrNewDir.length() - 1);
        }
        // delete '\\' 
        wstrNewDir.erase(wstrNewDir.length() - 1); // delete '\\' 
        // 递归进入
        RecursiveDirectory(wstrNewDir);  // 递归本函数，再创建目录
        // 递归退出后创建之前失败的目录
        CreateDirectory(wstrDir.c_str(), NULL);  // 递归返回，在存在的目录上再建目录
    }// 多级目录创建成功
}
void DeleteDstFile(string DstFile)
{
	wstring WStrDstFile = AnsiToUNICODE(DstFile);

	DeleteFile(LPCWSTR(WStrDstFile.c_str()));
}
void CopyDstFile(string SrcFile,string DstFile)
{
	wstring WStrSrcFile = AnsiToUNICODE(SrcFile);
	wstring WStrDstFile = AnsiToUNICODE(DstFile);

	CopyFile((LPCWSTR)WStrSrcFile.c_str(), (LPCWSTR)WStrDstFile.c_str(), false);
}
void SetDstFileAttributes(string DstFile, DWORD FileAttributes)
{
	wstring WStrDstFile = AnsiToUNICODE(DstFile);

	SetFileAttributes((LPCWSTR)WStrDstFile.c_str(), FileAttributes);
}


