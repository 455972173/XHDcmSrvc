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



