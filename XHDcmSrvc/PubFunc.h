//公共函数
#ifndef _PUBFUNC_H_
#define _PUBFUNC_H_
#include <iostream>
#include <algorithm>  
#include <cmath>  
#include <vector>  
#include <string>  
#include <cstring>
#include <atlbase.h>
#include <Windows.h>
#include<stdio.h>
#include<fstream>
#include "atlbase.h"
#include "Ini.h"
#include "Logger.h"
extern LOGGER::CLogger Logger;

//获取目的目录下的文件
bool getDstFiles(string path, string mode, vector<string>& files, bool IsOnlyName = false);
//将字符串中的指定字符转换成"_"
string CanvertToValidFileName(string AStr);
//判断文件或目录是否存在
bool IsFileExists(string Path);
//去掉字符串首尾的空格
void Trim(string &s);
//获取当前时间的字符串格式：YYYY-mm-dd HH:MM:SS
string GetCurTmStr();
//比较两个字符串大小 当s1<s2时，返回值<0，当s1 = s2时，返回值 = 0，当s1>s2时，返回值>0
int CompareNoCase(string str1, string str2);
//提取文件名
string ExtractFileName(string FileName);
#endif // !"_PUBFUNC_H_"

