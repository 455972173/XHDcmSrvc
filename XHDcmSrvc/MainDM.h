//数据库读写数据 Database Modify
#ifndef _MAINDM_H_
#define _MAINDM_H_
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include "Ini.h"
#include "Logger.h"
#include "ADOSQL.h"
#include "DCMObj.h"
#include "PubFunc.h"
using namespace std;
using namespace LOGGER;
using namespace ADO;
class MainDataModify
{
public:
	MainDataModify() {}
	~MainDataModify() {}
	bool ConnectDataBase(string ServerIp, string User, string Pwd, string DataBase);
	bool SaveDicomInfo(TDcmInfoHeader DcmInfoHeader,string SOPFileName);
	bool DcmSOPFound(string PatientID, string SOPInstanceUID, string& SOPFileName);
private:
	void ExecuteSQL(string SqlCmd);//执行sql语句

	bool DcmPatientExist(string PatientID, string& PatientName);//根据病人ID查看是否存在，取出病人姓名
	bool DcmStudyExist(string PatientID, string StudyInstanceUID);//判断对应的用户研究ID是否存在
	bool DcmSeriesExist(string PatientID, string SeriesInstanceUID);
	bool DcmSOPExist(string PatientID, string SOPInstanceUID);

	bool SaveDcmPatient(TDcmInfoHeader DcmInfoHeader);
	bool SaveDcmStudy(TDcmInfoHeader DcmInfoHeader);
	bool SaveDcmSeries(TDcmInfoHeader DcmInfoHeader);
	bool SaveDcmSOP(TDcmInfoHeader DcmInfoHeader,string SOPFileName);

	CADOSQL m_Sql;
};
#endif // !_MAINDM_H_

