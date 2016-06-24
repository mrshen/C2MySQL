#include <iostream>
#include "c2mysql.h"
using namespace std;

#define IS_DEBUG 1

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
				sql = "SELECT name, owner, species FROM pet";
				db.selectSQL(sql);
				break;
			case 3:
				sql = "UPDATE pet SET sex='f' WHERE name='Buffy' AND owner='Harold'";
				db.updateSQL(sql);
				break;
			case 4:
				sql = "DELETE FROM pet WHERE name='d'";
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