#include "stdafx.h"
#include "MainDM.h"

bool MainDataModify::ConnectDataBase(string ServerIp, string User, string Pwd, string DataBase)
{
	m_Sql.Connect(ServerIp, User, Pwd, DataBase);
	if (!m_Sql.IsOpen())
	{
		return false;
	}
	else
	{
		return true;
	}
}
void MainDataModify::ExecuteSQL(string SqlCmd)//执行sql语句
{
	m_Sql.Execute(SqlCmd);
}

bool MainDataModify::DcmPatientExist(string PatientID, string& PatientName)//根据病人ID查看是否存在，取出病人姓名
{
	string SqlCmd = "select PatientName from DcmPatient where PatientID=" + PatientID;
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (!CurRecordSet->EndOfFile)
	{
		PatientName = (char*)(_bstr_t)CurRecordSet->GetCollect("PatientName");
		return true;
	}
	return false;
}
bool MainDataModify::DcmStudyExist(string PatientID, string StudyInstanceUID)//判断对应的用户研究ID是否存在
{
	string SqlCmd = "select StudyInstUID from DcmStudy where PatientID=" + PatientID + " and StudyInstUID=" + StudyInstanceUID;
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (!CurRecordSet->EndOfFile)
	{
		return true;
	}
	return false;
}
bool MainDataModify::DcmSeriesExist(string PatientID, string SeriesInstanceUID)
{
	string SqlCmd = "select SeriesInstUID from DcmSeries where SeriesPatID=" + PatientID + " and SeriesInstUID=" + SeriesInstanceUID;
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (!CurRecordSet->EndOfFile)
	{
		return true;
	}
	return false;
}
bool MainDataModify::DcmSOPExist(string PatientID, string SOPInstanceUID)
{
	string SqlCmd = "select SOPInstUID from DcmSOP where PatientID=" + PatientID + " and SOPInstUID=" + SOPInstanceUID;
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (!CurRecordSet->EndOfFile)
	{
		return true;
	}
	return false;
}
bool MainDataModify::SaveDcmPatient(TDcmInfoHeader DcmInfoHeader)
{
	string PatientID = DcmInfoHeader.PatientID;
	string PatientName = DcmInfoHeader.PatientName;
	Trim(PatientName);
	string PatientBirthDate = DcmInfoHeader.PatientBirthDate;
	string PatientSex = DcmInfoHeader.PatientSex;
	string AccessTime = GetCurTmStr();
	string PrePatName;
	string SqlCmd;
	bool IsPatientExist = DcmPatientExist(PatientID, PrePatName);
	if (IsPatientExist && (CompareNoCase(PatientName, PrePatName) != 0))
	{
		return false;
	}
	char SqlCmdBuff[1024];
	memset(SqlCmdBuff, 0, 1024);
	if (!IsPatientExist)
	{
		snprintf(SqlCmdBuff, 1024, "insert into DcmPatient(PatientID, PatientName, Birthdate, PatientSex, AccessTime) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			PatientID.c_str(), PatientName.c_str(), PatientBirthDate.c_str(), PatientSex.c_str(), AccessTime.c_str());
	}
	else
	{
		snprintf(SqlCmdBuff, 1024, "update DcmPatient set PatientName=\'%s\', Birthdate=\'%s\', PatientSex= \'%s\', AccessTime= \'%s\' where PatientID=\'%s\'; ", PatientID.c_str(), PatientName.c_str(), PatientBirthDate.c_str(), PatientSex.c_str(), AccessTime.c_str());
	}
	ExecuteSQL(SqlCmdBuff);
	return true;
}
bool MainDataModify::SaveDcmStudy(TDcmInfoHeader DcmInfoHeader)
{

}
bool MainDataModify::SaveDcmSeries(TDcmInfoHeader DcmInfoHeader)
{

}
bool MainDataModify::SaveDcmSOP(TDcmInfoHeader DcmInfoHeader, string SOPFileName)
{

}


