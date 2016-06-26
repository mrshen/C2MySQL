#include "c2mysql.h"
#include <iostream>

using namespace std;

// 是否启动重连设置
#define ENABLE_RECONNECT 1

MyDB::MyDB()
{
	this->host = "localhost";
	this->user = "root";
	this->psw = "root1234";
	this->dbName = "jayz_test";
	
	if (NULL == mysql_init(&(this->connection)))
	{
		cout << "Error: " << mysql_error(&(this->connection)) << endl;
		exit(1);
	}

	cout << "====================MyDB() is being called.====================" << endl << endl;
}

MyDB::MyDB(string _dbName):MyDB()
{
	this->dbName = _dbName;
}

MyDB::MyDB(string _host, string _user, string _psw, string _dbName):MyDB(_dbName)
{
	this->host = _host;
	this->user = _user;
	this->psw = _psw;
}

MyDB::~MyDB()
{
	if (NULL != &(this->connection))
	{
		mysql_close(&(this->connection));
	}

	cout << endl << "====================~MyDB() is being called.====================" << endl;
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
		cout << "Error: " << mysql_error(&(this->connection)) << endl;
		return false;
	}

#if ENABLE_RECONNECT
	// 设置自动重连选项
	char val = 1;
	if (mysql_options(&(this->connection), MYSQL_OPT_RECONNECT, (const char*)&val))
	{
		cout << "Error: set RECONNECT failure." << endl;
	}
#endif // ENABLE_RECONNECT

	return true;
}

bool MyDB::showAllSQL()
{
	string sql = "select * from pet";
	return selectSQL(sql);
}

bool MyDB::selectSQL(string sql)
{
	// 调用mysql_query前最好先mysql_ping一下，以防断掉的连接重连回来
	mysql_ping(&(this->connection));
	if (mysql_query(&(this->connection), sql.c_str()))
	{
		cout << "Error: " << mysql_error(&(this->connection)) << endl;
		return false;
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
		while ((this->row = mysql_fetch_row(this->result)))
		{
			for (size_t i = 0; i < fieldsNum; ++i)
				cout << (this->row[i] ? this->row[i] : "NULL") << '\t';
			cout << endl;
		}
		cout << "total: " << rowsNum << " rows." << endl;

		// 释放资源
		mysql_free_result(this->result);
	}

	return true;
}

bool MyDB::executeSQL(string opType, string sql)
{
	// 调用mysql_query前最好先mysql_ping一下，以防断掉的连接重连回来
	mysql_ping(&(this->connection));
	if (mysql_query(&(this->connection), sql.c_str()))
	{
		cout << "Error: " << mysql_error(&(this->connection)) << endl;
		// exit(1);
		return false;
	}
	else
	{
		if (!mysql_field_count(&(this->connection)))
		{
			cout << "[" << opType << "] affected: " << mysql_affected_rows(&(this->connection)) << " rows." << endl;
			return /*showAllSQL()*/true;
		}
		else
		{
			cout << "you execute a SELECT.." << endl;
			return false;
		}
	}
}

void MyDB::updateSQL(string sql)
{
	if (executeSQL("UPDATE", sql)) {
		cout << "update done.." << endl;
	}
}

void MyDB::deleteSQL(string sql)
{
	if (executeSQL("DELETE", sql)) {
		cout << "delete done.." << endl;
	}
}

string MyDB::insertHelper()
{
	string name, owner, species, sex, birth, death;
	cout << "name: ";
	cin >> name;
	cout << "owner: ";
	cin >> owner;
	cout << "species: ";
	cin >> species;
	cout << "sex (f/m): ";
	cin >> sex;
	cout << "birth (YYYY-MM-DD): ";
	cin >> birth;
	cout << "death (YYYY-MM-DD): ";
	cin >> death;

	string sql = "INSERT INTO pet(name, owner, species, sex, birth, death) VALUES('"
		+ name + "', '"
		+ owner + "', '"
		+ species + "', '"
		+ sex + "', '"
		+ birth + "', '"
		+ death + "')";
	return sql;
}

void MyDB::insertSQL()
{
	string sql = insertHelper();
	if (executeSQL("INSERT", sql))
	{
		cout << "insert done.." << endl;
	}
}