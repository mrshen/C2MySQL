#pragma once
#ifndef C2MYSQL_H
#define C2MYSQL_H

#include <Windows.h>
#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

class MyDB
{
public:
	// 构造函数
	MyDB();
	MyDB(string _dbName);
	MyDB(string _host, string _user, string _psw, string _dbName);
	// 析构函数
	~MyDB();
	// 数据库初始化函数
	bool initDB();
	// 数据库sql执行函数
	bool showAllSQL();
	
	bool selectSQL(string sql);
	void updateSQL(string sql);
	void deleteSQL(string sql);
	void insertSQL();

protected:
	bool executeSQL(string opType, string sql);
	string insertHelper();

private:
	// mysql连接
	MYSQL connection;
	// mysql执行结果集
	MYSQL_RES *result;
	MYSQL_ROW row;

	// 主机host
	string host;
	// 数据库登录用户user
	string user;
	// 数据库登录密码psw
	string psw;
	// 要操作的数据库dbName
	string dbName;
};

#endif // !C2MYSQL_H