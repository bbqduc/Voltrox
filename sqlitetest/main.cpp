#include <sqlite3.h>
#include <iostream>
#include <cstring>
#include <stdint.h>


int main()
{

	sqlite3* db;

	sqlite3_open(":memory:", &db);

	if(db)
		std::cout << "Opened database!\n";
	else
		std::cout << "Error opening database!\n";

	sqlite3_stmt* statement;
	const char* cmd = "CREATE TABLE entities (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, debugname VARCHAR(50));";
	sqlite3_prepare(db, cmd, 1+strlen(cmd), &statement, NULL);
	if(!statement)
	{
		std::cout << "Failed to create statement1!\n";
		return -1;
	}

	if(SQLITE_ERROR == sqlite3_step(statement))
	{
		std::cout << "Error executing statement!\n";
		return -1;
	}
	sqlite3_finalize(statement);

	const char* cmd2 = "INSERT INTO entities (debugname) VALUES ('TROLLO');";
	sqlite3_prepare(db, cmd2, 1+strlen(cmd2), &statement, NULL);

	if(!statement)
	{
		std::cout << "Failed to create statement2!\n";
		return -1;
	}

	if(SQLITE_ERROR == sqlite3_step(statement))
	{
		std::cout << "Error executing statement!\n";
		return -1;
	}
	sqlite3_finalize(statement);

	const char* cmd3 = "SELECT * FROM entities;";
	sqlite3_prepare(db, cmd3, 1+strlen(cmd3), &statement, NULL);
	
	if(SQLITE_ERROR == sqlite3_step(statement))
	{
		std::cout << "Error executing statement!\n";
		return -1;
	}

	int64_t res = sqlite3_column_int64(statement, 0);
	int columns = sqlite3_column_count(statement);
	const unsigned char* res2 = sqlite3_column_text(statement, 1);

	std::cout << "GOT COLUMNS " << res << '\n';
	std::cout << "GOT RESULT " << res << '\n';
	std::cout << "GOT RESULT " << res2 << '\n';

	sqlite3_finalize(statement);
}