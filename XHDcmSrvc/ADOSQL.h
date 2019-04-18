//ado操作数据库
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
		bool Execute(const string& exec);	// 无返回值的操作
		_RecordsetPtr Query(const string& CommandStr, VARIANT * RecordsAffected = NULL);	//有返回值的操作(查询)
	private:
		_ConnectionPtr m_pConn;//创建Connection对象
		_RecordsetPtr m_pRecordset;//创建记录集

		string m_strDatabase;//数据库名称
		string m_strUser;//数据库用户名
		string m_strPsw;//数据库密码
		string m_strServer;////数据库服务器的地址
		bool m_bTransactionError;//开始事务是否异常
		long m_lRecordCount;//得到的记录条数
		bool m_bTransaction;//是否开始事务

	private:
		CADOSQL(void);
		void dump_com_error(_com_error &e);	//出错处理
	};
}
#endif