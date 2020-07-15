#pragma once
#include "Database.h"
#pragma warning(disable:4996)

class DatabaseManager
{
private:
	Database* db;
	void printEnterTableName()const;
	void printEnterFileName()const;
	void printEnterValue();
	
public:
	DatabaseManager();
	Database* GetInstance();
	~DatabaseManager();
	void showCommands();
	void enterCommandNum(int& number);
};

