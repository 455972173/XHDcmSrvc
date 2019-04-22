#include "stdafx.h"
#include "PubFunc.h"
#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//�ҵ�Ŀ��Ŀ¼�µ�ָ���ļ���ֻ��modeΪ*.*��ʱ��֧�ֵݹ���������ļ�
//IsOnlyNameΪtrue��ʱ��õ���vector����ŵĶ����ļ�����Ϊfalse��ʱ��ŵ��Ǿ���·��
bool getDstFiles(string path, string mode, vector<string>& files,bool IsOnlyName)
{
	//�ļ����  
	long hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
	string p;  //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
	p.assign(path).append(mode.c_str());
	if ((hFile = _findfirst(p.c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //�Ƚ��ļ������Ƿ����ļ���
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
		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
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
//���ַ����е�ָ���ַ�ת����"_"
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
	strftime(TmBuff, sizeof(TmBuff), "%Y-%m-%d %H:%M:%S", CurTm); //��-��-�� ʱ-��-��
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
	// ���ֽ�ת���ֽ�
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
	// ���ֽ�ת���ֽ�
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
void __fastcall RecursiveDirectory(wstring wstrDir) // ������Ŀ¼
{
    if (wstrDir.length() <= 3)//�Ǹ�Ŀ¼�����贴��Ŀ¼
    {
        return;
    }
    if (wstrDir[wstrDir.length() - 1] == '\\')   // ��·����ΪĿ¼
    {
        wstrDir.erase(wstrDir.end() - 1);
    }
    // �޸��ļ�����
    WIN32_FIND_DATA wfd;
    HANDLE hFind = FindFirstFile(wstrDir.c_str(), &wfd); // ����
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FindClose(hFind);
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            return;
    }
    // ������ǰĿ¼�ĵ�Ŀ¼ʧ��
    if (CreateDirectory(wstrDir.c_str(), NULL) == false)
    {// �˵���һ��Ŀ¼
        wstring wstrNewDir = wstrDir;
        while (wstrNewDir[wstrNewDir.length()-1] != '\\')     // ������ǰĿ¼����һ��Ŀ¼
        {
            wstrNewDir.erase(wstrNewDir.length() - 1);
        }
        // delete '\\' 
        wstrNewDir.erase(wstrNewDir.length() - 1); // delete '\\' 
        // �ݹ����
        RecursiveDirectory(wstrNewDir);  // �ݹ鱾�������ٴ���Ŀ¼
        // �ݹ��˳��󴴽�֮ǰʧ�ܵ�Ŀ¼
        CreateDirectory(wstrDir.c_str(), NULL);  // �ݹ鷵�أ��ڴ��ڵ�Ŀ¼���ٽ�Ŀ¼
    }// �༶Ŀ¼�����ɹ�
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


