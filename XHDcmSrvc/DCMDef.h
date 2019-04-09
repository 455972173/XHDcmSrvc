//DCM格式解析的相关结构体
#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

typedef struct DcmInfoHeader
{    
	////Patient
	string m_PatientID;
	string m_PatientName;
	string m_PatientSex;
	string m_PatientBirthDate;
	//PatientBirthTime:
	//PatientAge;     
	////General Study
	string m_StudyInstanceUID;
	string m_StudyID;
	string m_StudyDate;
	string m_StudyTime;
	string m_StudyDescript;
	string m_AccessionNo;
	string m_ReferPhysician;
	////Series
	string m_SeriesInstanceUID;
	string m_Modality;
	string m_SeriesNo;
	string m_SeriesDate;
	string m_SeriesTime;
	string m_SeriesDescript;
	string m_BodyPartExam;
	////General Equipment
	string m_StationName;
	string m_InstituteName;
	string m_Manufacturer;
	string m_ModelName;
	////SOP Common
	string m_SOPClassUID;
	string m_SOPClassName;
	string m_SOPInstanceUID;
	string m_InstanceNo;
	////
	string m_DcmFileName;
}*PDcmInfoHeader;
typedef struct DcmImageInfo
{
	long m_Size;
	long m_FrameCount;
	long m_FrameIndex;
	long m_Width;
	long m_Height;
	long m_Depth;
	double m_MinValue;
	double m_MaxValue;
	double m_AspectRatio;
	long m_Monochrome;
	long m_WindowCount;
	double m_WinCenter;
	double m_WinWidth;
	char* m_PixelSpacing;
}*PDcmImageInfo;