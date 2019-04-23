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
bool MainDataModify::SaveDicomInfo(TDcmInfoHeader DcmInfoHeader, string SOPFileName)
{
	if (!SaveDcmPatient(DcmInfoHeader))
	{
		return false;
	}
	SaveDcmStudy(DcmInfoHeader);
	SaveDcmSeries(DcmInfoHeader);
	SaveDcmSOP(DcmInfoHeader, SOPFileName);
	return true;
}
bool MainDataModify::DcmSOPFound(string PatientID, string SOPInstanceUID, string& SOPFileName)
{
	char CmdBuf[1024];
	memset(CmdBuf, 0, 1024);
	snprintf(CmdBuf,1024,"select ObjectFile from DcmSOP where PatientID=\'%s\' and SOPInstUID=\'%s\' ", PatientID.c_str(), SOPInstanceUID.c_str());
	_RecordsetPtr CurRecordSet = m_Sql.Query(CmdBuf);
	if (CurRecordSet == NULL)
	{
		return false;
	}
	if (!CurRecordSet->EndOfFile)//如果能够找到
	{
		return true;
		SOPFileName = CurRecordSet->GetCollect("ObjectFile");
	}
	return false;
}
void MainDataModify::ExecuteSQL(string SqlCmd)//执行sql语句
{
	m_Sql.Execute(SqlCmd);
}

bool MainDataModify::DcmPatientExist(string PatientID, string& PatientName)//根据病人ID查看是否存在，取出病人姓名
{
	string SqlCmd = "select PatientName from DcmPatient where PatientID=\'" + PatientID + "\'";
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (CurRecordSet == NULL)
	{
		return false;
	}
	if (!CurRecordSet->EndOfFile)
	{
		PatientName = (char*)(_bstr_t)CurRecordSet->GetCollect("PatientName");
		return true;
	}
	return false;
}
bool MainDataModify::DcmStudyExist(string PatientID, string StudyInstanceUID)//判断对应的用户研究ID是否存在
{
	string SqlCmd = "select StudyInstUID from DcmStudy where PatientID=\'" + PatientID + "\' and StudyInstUID=\'" + StudyInstanceUID + "\'";
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (CurRecordSet == NULL)
	{
		return false;
	}
	if (!CurRecordSet->EndOfFile)
	{
		return true;
	}
	return false;
}
bool MainDataModify::DcmSeriesExist(string PatientID, string SeriesInstanceUID)
{
	string SqlCmd = "select SeriesInstUID from DcmSeries where SeriesPatID=\'" + PatientID + "\' and SeriesInstUID=\'" + SeriesInstanceUID + "\'";
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (CurRecordSet == NULL)
	{
		return false;
	}
	if (!CurRecordSet->EndOfFile)
	{
		return true;
	}
	return false;
}
bool MainDataModify::DcmSOPExist(string PatientID, string SOPInstanceUID)
{
	string SqlCmd = "select SOPInstUID from DcmSOP where PatientID=\'" + PatientID + "\' and SOPInstUID=\'" + SOPInstanceUID + "\'";
	_RecordsetPtr CurRecordSet = m_Sql.Query(SqlCmd);
	if (CurRecordSet == NULL)
	{
		return false;
	}
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
	char SqlCmdBuff[2048];
	memset(SqlCmdBuff, 0, 2048);
	if (!IsPatientExist)
	{
		snprintf(SqlCmdBuff, 2048, "insert into DcmPatient(PatientID, PatientName, Birthdate, PatientSex, AccessTime) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			PatientID.c_str(), PatientName.c_str(), PatientBirthDate.c_str(), PatientSex.c_str(), AccessTime.c_str());
	}
	else
	{
		snprintf(SqlCmdBuff, 2048, "update DcmPatient set PatientName=\'%s\', Birthdate=\'%s\', PatientSex= \'%s\', AccessTime= \'%s\' where PatientID=\'%s\'; ",
			PatientID.c_str(), PatientName.c_str(), PatientBirthDate.c_str(), PatientSex.c_str(), AccessTime.c_str());
	}
	ExecuteSQL(SqlCmdBuff);
	return true;
}
bool MainDataModify::SaveDcmStudy(TDcmInfoHeader DcmInfoHeader)
{
	string SQLStr;
	char SqlCmdBuff[2048];
	memset(SqlCmdBuff, 0, 2048);
	string AccessTimeStr = GetCurTmStr();
	if (!DcmStudyExist(DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID))
	{
		snprintf(SqlCmdBuff, 2048, "insert into DcmStudy(StudyInstUID, StudyDate, StudyTime, StudyID, StudyDescript, AccessionNo, ReferPhysician, StationName, InstituteName, PatientID, AccessTime) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			DcmInfoHeader.StudyInstanceUID, DcmInfoHeader.StudyDate, DcmInfoHeader.StudyTime, DcmInfoHeader.StudyID, DcmInfoHeader.StudyDescript, DcmInfoHeader.AccessionNo, DcmInfoHeader.ReferPhysician, DcmInfoHeader.StationName, DcmInfoHeader.InstituteName, DcmInfoHeader.PatientID, AccessTimeStr.c_str());
	}
	else
	{
		snprintf(SqlCmdBuff, 2048, "update DcmStudy set StudyDate=\'%s\',StudyTime=\'%s\',StudyID=\'%s\',StudyDescript=\'%s\',AccessionNo=\'%s\',ReferPhysician = \'%s\',StationName=\'%s\',InstituteName=\'%s\',PatientID=\'%s\',AccessTime=\'%s\',where StudyInstUID = \'%s\'",
			DcmInfoHeader.StudyDate, DcmInfoHeader.StudyTime, DcmInfoHeader.StudyID, DcmInfoHeader.StudyDescript, DcmInfoHeader.AccessionNo, DcmInfoHeader.ReferPhysician, DcmInfoHeader.StationName, DcmInfoHeader.InstituteName, DcmInfoHeader.PatientID, AccessTimeStr.c_str(),DcmInfoHeader.StudyInstanceUID);
	}
	ExecuteSQL(SqlCmdBuff);
	return true;
}
bool MainDataModify::SaveDcmSeries(TDcmInfoHeader DcmInfoHeader)
{
	string SQLStr;
	char SqlCmdBuff[2048];
	memset(SqlCmdBuff, 0, 2048);
	string AccessTimeStr = GetCurTmStr();
	if (!DcmSeriesExist(DcmInfoHeader.PatientID, DcmInfoHeader.SeriesInstanceUID))
	{
		snprintf(SqlCmdBuff, 2048, "insert into DcmSeries(SeriesInstUID, SeriesDate, SeriesTime, SeriesNo, SeriesDescript, Modality, Manufacturer, ModelName, BodyPartExam, SeriesPatID,StudyInstUID, AccessTime) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			DcmInfoHeader.SeriesInstanceUID, DcmInfoHeader.SeriesDate, DcmInfoHeader.SeriesTime, DcmInfoHeader.SeriesNo, DcmInfoHeader.SeriesDescript, DcmInfoHeader.Modality, DcmInfoHeader.Manufacturer, DcmInfoHeader.ModelName, DcmInfoHeader.BodyPartExam, DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID, AccessTimeStr.c_str());
	}
	else
	{
		snprintf(SqlCmdBuff, 2048, "update DcmSeries set SeriesDate=\'%s\',SeriesTime=\'%s\',SeriesNo=\'%s\',SeriesDescript=\'%s\',Modality=\'%s\',Manufacturer = \'%s\',ModelName=\'%s\',BodyPartExam=\'%s\',SeriesPatID=\'%s\',StudyInstUID=\'%s\',AccessTime=\'%s\',where StudyInstUID = \'%s\'",
			DcmInfoHeader.SeriesDate, DcmInfoHeader.SeriesTime, DcmInfoHeader.SeriesNo, DcmInfoHeader.SeriesDescript, DcmInfoHeader.Modality, DcmInfoHeader.Manufacturer, DcmInfoHeader.ModelName, DcmInfoHeader.BodyPartExam, DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID, AccessTimeStr.c_str(), DcmInfoHeader.StudyInstanceUID);
	}
	ExecuteSQL(SqlCmdBuff);
	return true;
}
bool MainDataModify::SaveDcmSOP(TDcmInfoHeader DcmInfoHeader, string SOPFileName)
{
	string SQLStr;
	char SqlCmdBuff[2048];
	memset(SqlCmdBuff, 0, 2048);
	string AccessTimeStr = GetCurTmStr();
	if (!DcmSOPExist(DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID))
	{
		snprintf(SqlCmdBuff, 2048, "insert into DcmSOP(SOPInstUID, SOPClassUID, InstanceNo, PatientID, StudyInstUID, SeriesInstUID, ObjectFile, AccessTime) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",
			DcmInfoHeader.SOPInstanceUID, DcmInfoHeader.SOPClassUID, DcmInfoHeader.InstanceNo, DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID, DcmInfoHeader.SeriesInstanceUID, SOPFileName.c_str(), AccessTimeStr.c_str());
	}
	else
	{
		snprintf(SqlCmdBuff, 2048, "update DcmSOP set SOPClassUID=\'%s\',InstanceNo=\'%s\',PatientID=\'%s\',StudyInstUID=\'%s\',SeriesInstUID=\'%s\',ObjectFile = \'%s\',AccessTime=\'%s\',where SOPInstUID = \'%s\'",
			 DcmInfoHeader.SOPClassUID, DcmInfoHeader.InstanceNo, DcmInfoHeader.PatientID, DcmInfoHeader.StudyInstanceUID, DcmInfoHeader.SeriesInstanceUID, SOPFileName.c_str(), AccessTimeStr.c_str(), DcmInfoHeader.SOPInstanceUID);
	}
	ExecuteSQL(SqlCmdBuff);
	return true;
}


