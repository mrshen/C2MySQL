#include <iostream>
#include "c2mysql.h"
using namespace std;

int main()
{
	//const string host = "localhost";
	//const string user = "root";
	//const string pswd = "root1234";
	//const string dbName = "jayz_test";

	//const string sql = "SELECT * FROM pet";

	MyDB db;
	db.initDB();
	//db.execSQL(sql);
	db.showAllSQL();

	return 0;
}