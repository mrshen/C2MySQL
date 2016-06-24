#include "c2mysql.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MyDB::MyDB()
{
	this->host = "localhost";
	this->user = "root";
	this->psw = "root1234";
	this->dbName = "jayz_test";
	
	if (NULL == mysql_init(&(this->connection)))
	{
		cout << "Error: " << mysql_error(&(this->connection));
		exit(1);
	}

	cout << "MyDB() is being called." << endl;
}

MyDB::MyDB(string _dbName)
{
	MyDB();
	this->dbName = _dbName;
}

MyDB::MyDB(string _host, string _user, string _psw, string _dbName)
{
	MyDB();
	this->host = _host;
	this->user = _user;
	this->psw = _psw;
	this->dbName = _dbName;
}

MyDB::~MyDB()
{
	if (NULL != &connection)
	{
		mysql_close(&(this->connection));
	}

	cout << "~MyDB() is being called." << endl;
}

bool MyDB::initDB()
{
	
	if (NULL == mysql_real_connect(
		&(this->connection),
		this->host.c_str(),
		this->user.c_str(),
		this->psw.c_str(),
		this->dbName.c_str(),
		0,
		NULL,
		0))
	{
		cout << "Error: " << mysql_error(&(this->connection));
		exit(1);
	}

	return true;
}

bool MyDB::showAllSQL()
{
	string sql = "select * from pet";

	if (mysql_query(&(this->connection), sql.c_str()))
	{
		cout << "Error: " << mysql_error(&(this->connection));
		exit(1);
	}
	else
	{
		// 一次性获取全部数据
		this->result = mysql_store_result(&(this->connection));
		//size_t rowsNum = mysql_field_count(&connection);
		// 查询结果的行数
		size_t rowsNum = mysql_num_rows(this->result);
		// 查询结果的字段数
		size_t fieldsNum = mysql_num_fields(this->result);

		// 打印字段名
		MYSQL_FIELD *field = NULL;
		for (size_t ind = 0; ind < fieldsNum; ++ind)
		{
			field = mysql_fetch_field_direct(this->result, ind);
			cout << field->name << '\t';
		}
		cout << endl;

		// 逐行打印数据
		this->row = mysql_fetch_row(this->result);
		while (this->row != NULL)
		{
			for (size_t i = 0; i < fieldsNum; ++i) {
				if (this->row[i] == NULL)
					cout << "NULL\t";
				else
					cout << this->row[i] << '\t';
			}
			cout << endl;
			this->row = mysql_fetch_row(this->result);
		}
		cout << "total: " << rowsNum << " rows." << endl;

		// 释放资源
		mysql_free_result(this->result);
	}

	return true;
}