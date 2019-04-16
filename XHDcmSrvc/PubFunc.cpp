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



