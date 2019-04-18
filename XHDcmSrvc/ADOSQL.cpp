#include "stdafx.h"
#include "iostream"
#include "iomanip"
#include "windows.h"
#include "ADOSQL.h"
using namespace std;
namespace ADO
{
	CADOSQL::CADOSQL()
	{
		CoInitialize(NULL);;//��ʼ��OLE/COM�⻷����Ϊ����ADO�ӿ���׼��
		m_bTransactionError = false;
		m_bTransaction = false;
		m_lRecordCount = 0;

		m_pConn.CreateInstance(__uuidof(Connection));//����Connection����
		m_pRecordset.CreateInstance(__uuidof(Recordset));//������¼��
	}

	CADOSQL::~CADOSQL(void)
	{
		Close();
		m_pRecordset.Release();
		m_pConn.Release();
		CoUninitialize();
	}
	bool CADOSQL::Close(void)
	{
		if (m_pConn == NULL || !IsOpen())
			return false;
		m_pConn->Close();
		return true;
	}
	bool CADOSQL::Connect(string ServerIp, string User, string Pwd, string DataBase)
	{
		m_strServer = ServerIp;//127.0.0.1,1433
		m_strUser = User;
		m_strPsw = Pwd;
		m_strDatabase = DataBase;

		string conData = "Provider=SQLOLEDB;Server=";//Provider=SQLOLEDB ���ݿ����SQL�ķ�ʽ����
		conData += m_strServer;//���ݿ�������ĵ�ַ
		conData += ";uid=";
		conData += m_strUser;//�û���
		conData += ";pwd=";
		conData += m_strPsw;//����
		conData += ";database=";
		conData += m_strDatabase;//���ݿ�Ŀ���

		try
		{
			HRESULT hRet = m_pConn->Open(conData.c_str(), "", "", adConnectUnspecified);//��¼���ݿ�
			if (!SUCCEEDED(hRet))
				return false;
		}
		catch (_com_error &comError)
		{
			dump_com_error(comError);
			return false;
		}
		return true;
	}
	bool CADOSQL::IsOpen(void)
	{
		try
		{
			return (m_pConn != NULL && (m_pConn->State & adStateOpen));
		}
		catch (_com_error &e)
		{
			dump_com_error(e);
		}
		return false;
	}
	void CADOSQL::dump_com_error(_com_error &e)
	{
		string ErrorStr;
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		ErrorStr = "MAdoDataBase Error=";
		ErrorStr += "\n\tSource =";
		ErrorStr += (LPCSTR)bstrSource;
		ErrorStr += "\n\tDescripiion =";
		ErrorStr += (LPCSTR)bstrDescription;
	}
	// �޷���ֵ�Ĳ���
	bool CADOSQL::Execute(const string &exec)
	{
		if (m_pConn == NULL || exec.empty() || !IsOpen())
			return false;
		try
		{
			if (m_bTransaction && m_bTransactionError)
				return false;

			m_pConn->Execute(exec.c_str(), NULL, adExecuteNoRecords);
			return true;
		}
		catch (_com_error &e)
		{
			if (m_bTransaction)
			{
				m_bTransactionError = true;
			}
			dump_com_error(e);
		}
		return false;
	}
	//�з���ֵ�Ĳ���(��ѯ)
	//Variant ��һ��������������ͣ����˶��� String ���ݼ��û����������⣬���԰����κ����������
	_RecordsetPtr CADOSQL::Query(const string &CommandStr, VARIANT * RecordsAffected)
	{
		try
		{
			if (!IsOpen())
			{
				return NULL;
			}
			m_pRecordset = m_pConn->Execute(CommandStr.c_str(), RecordsAffected, adModeUnknown);
			m_lRecordCount = GetRecordCount(m_pRecordset);
			return m_pRecordset;
		}
		catch (_com_error& e)
		{
			dump_com_error(e);
			return NULL;
		}
	}
	//������¼����ȡ������
	long CADOSQL::GetRecordCount(_RecordsetPtr set)
	{
		long nCount = 0;

		if (!set->EndOfFile)
		{
			set->MoveFirst();
			while (!set->EndOfFile)
			{
				++nCount;
				set->MoveNext();
			}
			set->MoveFirst();
		}
		return nCount;
	}
}