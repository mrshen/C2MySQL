#include <iostream>
#include "c2mysql.h"
using namespace std;

int main()
{
	string sql;

	MyDB db/*("10.123.7.17", "root", "root1234", "jayz_test")*/;
	if (db.initDB()) {
		int choice;
		do
		{
			choice = 0;
			cout << "1 for showAll, 2 for select, 3 for update, 4 for delete, 5 for insert, 0 to quit" << endl;
			cout << "choice> ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				db.showAllSQL();
				break;
			case 2:
				cout << "select sql> ";
				getchar();
				getline(cin, sql);
				db.selectSQL(sql);
				break;
			case 3:
				cout << "update sql> ";
				getchar();
				getline(cin, sql);
				db.updateSQL(sql);
				break;
			case 4:
				cout << "delete sql> ";
				getchar();
				getline(cin, sql);
				db.deleteSQL(sql);
				break;
			case 5:
				db.insertSQL();
				break;
			default:
				choice = 0;
				break;
			}
		} while (choice);
	}
	else
	{
		cout << "initial failure." << endl;
	}

	return 0;
}