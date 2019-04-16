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
#endif // !"_PUBFUNC_H_"

