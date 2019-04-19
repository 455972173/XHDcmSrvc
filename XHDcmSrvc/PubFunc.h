//��������
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
//ȥ���ַ�����β�Ŀո�
void Trim(string &s);
//��ȡ��ǰʱ����ַ�����ʽ��YYYY-mm-dd HH:MM:SS
string GetCurTmStr();
//�Ƚ������ַ�����С ��s1<s2ʱ������ֵ<0����s1 = s2ʱ������ֵ = 0����s1>s2ʱ������ֵ>0
int CompareNoCase(string str1, string str2);
//��ȡ�ļ���
string ExtractFileName(string FileName);
#endif // !"_PUBFUNC_H_"

