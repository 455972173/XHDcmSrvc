//ado�������ݿ�
#ifndef _ADOSQL_H_
#define _ADOSQL_H_
#include "stdafx.h"
#include <Windows.h>
#include <string>
using namespace std;
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")rename("BOF","adoBOF")
namespace ADO
{
	class CADOSQL
	{
	public:
		CADOSQL();
		~CADOSQL(void);

		bool Connect(string ServerIp, string User, string Pwd, string DataBase);
		bool Close(void);
		bool IsOpen(void);
		long GetRecordCount(_RecordsetPtr set);
		bool Execute(const string& exec);	// �޷���ֵ�Ĳ���
		_RecordsetPtr Query(const string& CommandStr, VARIANT * RecordsAffected = NULL);	//�з���ֵ�Ĳ���(��ѯ)
	private:
		_ConnectionPtr m_pConn;//����Connection����
		_RecordsetPtr m_pRecordset;//������¼��

		string m_strDatabase;//���ݿ�����
		string m_strUser;//���ݿ��û���
		string m_strPsw;//���ݿ�����
		string m_strServer;////���ݿ�������ĵ�ַ
		bool m_bTransactionError;//��ʼ�����Ƿ��쳣
		long m_lRecordCount;//�õ��ļ�¼����
		bool m_bTransaction;//�Ƿ�ʼ����

	private:
		CADOSQL(void);
		void dump_com_error(_com_error &e);	//������
	};
}
#endif