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

//��ȡĿ��Ŀ¼�µ��ļ�
bool getDstFiles(string path, string mode, vector<string>& files, bool IsOnlyName = false);
//���ַ����е�ָ���ַ�ת����"_"
string CanvertToValidFileName(string AStr);
//�ж��ļ���Ŀ¼�Ƿ����
bool IsFileExists(string Path);
#endif // !"_PUBFUNC_H_"

