#include "DatabaseManager.h"

DatabaseManager::~DatabaseManager()
{
}

void DatabaseManager::showCommands()
{
	std::cout << "Create Table: Number-0" << std::endl;
	std::cout << "import <file name>: Number-1 " << std::endl;
	std::cout << "showtables: Number-2" << std::endl;
	std::cout << "describe <name>: Number-3" << std::endl;
	std::cout << "print <name>: Number-4" << std::endl;
	std::cout << "export <name>: <file name> Number-5" << std::endl;
	std::cout << "select <column-n> <value> <table name>: Number-6" << std::endl;
	std::cout << "addcolumn <table name> <column name> <column type>: Number-7" << std::endl;
	std::cout << "update <table name> <search column n> <search value> <target column n> <target value>: Number-8" << std::endl;
	std::cout << "delete <table name> <search column n> <search value>: Number-9" << std::endl;
	std::cout << "insert <table name> <column 1> … <column n>: Number-10 " << std::endl;
	std::cout << "innerjoin <table 1> <column n1> <table 2> <column n2>: Number-11" << std::endl;
	std::cout << "rename <old name> <new name>: Number-12" << std::endl;
	std::cout << "count <table name> <search column n> <search value>: Number-13" << std::endl;
	std::cout << "aggregate <table name> <search column n> <search value> <target column n> <operation>: Number-14" << std::endl;
	std::cout << "Exit database: Number-16"<<std::endl;
}

void DatabaseManager::enterCommandNum(int& command)
{
	
	if(command==0)
	{
		std::cout << "Create Table: " << std::endl;
		db->addTable();
		return;
	}
	if (command == 1) 
	{
		std::cout << "Enter file name: ";
		char* fileName = new char[30];
		std::cin.getline(fileName,25);
		std::cin.clear();
		strcat(fileName, ".bin");
		
		db->importTableFromFile(fileName);
		delete[] fileName;
		return;
	}
	if (command == 2) 
	{
		db->printTableNames();
		return;
	}
	if (command == 3) 
	{
		printEnterTableName();

		char* tableName = new char[30];
		std::cin >> tableName;
		db->showTableTypes(tableName);
		delete[] tableName;
		return;
	}
	if (command == 4) 
	{
		printEnterTableName();
		char* tableName = new char[30];
		std::cin >> tableName;

		std::cin.clear();
		std::cin.ignore();

		db->print(tableName);
		delete[] tableName;
		return;
	}
	if (command == 5) 
	{
		char* tableName = new char[30];
		char* fileName = new char[30];

		printEnterTableName();
		
		std::cin.getline(tableName,30);
		std::cin.clear();

		std::cout << "Enter file name: ";
		std::cin.getline(fileName,30);
		std::cin.clear();
		
		db->exportTableToFile(tableName, fileName);
		delete[] tableName;
		delete[] fileName;
		return;
	}
	if (command == 6) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		char* value = new char[100];
		printEnterValue();
		std::cin.getline(value, 100);
		std::cin.clear();
		db->selectColumnsByValueAndTableName(tableName, value);

		delete[] tableName;
		delete[] value;
		return;
	}
	if (command == 7) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		std::cout << "Enter column name: ";
		char* columnName = new char[100];
		std::cin.getline(columnName, 99);
		std::cin.clear();

		std::cout << "Enter column type: ";
		char* columnType = new char[20];
		std::cin.getline(columnType, 19);
		std::cin.clear();

		db->addColumnToTableByGivenName(tableName, columnType, columnName);
		delete[] tableName;
		delete[] columnName;
		delete[] columnType;
	}
	if (command == 8) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		std::cout << "Enter column name: ";
		char* columnName = new char[100];
		std::cin.getline(columnName, 99);
		std::cin.clear();

		std::cout << "Enter  column value: ";
		char* value = new char[100];
		printEnterValue();
		std::cin.getline(value, 100);
		std::cin.clear();

		std::cout << "Enter target column name: ";
		char* targetColumName = new char[100];
		std::cin.getline(columnName, 99);
		std::cin.clear();

		std::cout << "Enter target column value: ";
		char* targetColumValue = new char[100];
		std::cin.getline(targetColumValue, 99);
		std::cin.clear();
		//To do
	}
	if (command == 9) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();


		std::cout << "Enter column name: ";
		char* columnName = new char[100];
		std::cin.getline(columnName, 99);
		std::cin.clear();

		
		char* value = new char[100];
		printEnterValue();
		std::cin.getline(value, 100);
		std::cin.clear();

		db->deleteColumnsByGivenValue(tableName, columnName, value);
		delete[] tableName;
		delete[] columnName;
		delete[] value;
	}
	if (command == 10) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();
		db->addColumns(tableName);
		
		
		
		delete[] tableName;
	}
	if (command == 11) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		char* tableColumnName = new char[100];
		std::cout << "Enter column name";
		std::cin.getline(tableColumnName, 99);
		std::cin.clear();

		char* tableTwoName = new char[100];
		printEnterTableName();
		std::cin.getline(tableTwoName, 99);
		std::cin.clear();

		char* tableTwoColumnName = new char[100];
		std::cout << "Enter column name";
		std::cin.getline(tableTwoColumnName, 99);
		std::cin.clear();

		db->innerJoin(tableName, tableTwoName, tableColumnName, tableTwoColumnName);
		delete[] tableName;
		delete[] tableColumnName;
		delete[] tableTwoName;
		delete[] tableTwoColumnName;
	}
	if (command == 12) 
	{
		char* tableName = new char[100];
		std::cout << "Enter old table name";
		std::cin.getline(tableName, 99);
		std::cin.clear();

		char* newTableName = new char[100];
		std::cout << "Enter new table name";
		db->renameTableName(tableName, newTableName);

		delete[] tableName;
		delete[] newTableName;

	}
	if (command == 13) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		char* tableColumnName = new char[100];
		std::cout << "Enter column name";
		std::cin.getline(tableColumnName, 99);
		std::cin.clear();

		char* value = new char[100];
		printEnterValue();
		std::cin.getline(value, 100);
		std::cin.clear();

		db->countRecords(tableName, tableColumnName, value);
		delete[] tableName;
		delete[] tableColumnName;
		delete[] value;

	}
	if (command == 14) 
	{
		char* tableName = new char[100];
		printEnterTableName();
		std::cin.getline(tableName, 99);
		std::cin.clear();

		char* tableColumnName = new char[100];
		std::cout << "Enter column name";
		std::cin.getline(tableColumnName, 99);
		std::cin.clear();

		char* value = new char[100];
		printEnterValue();
		std::cin.getline(value, 100);
		std::cin.clear();


		char* targetColumn = new char[100];
		std::cout << "Enter target column name: ";
		std::cin.getline(targetColumn, 99);
		std::cin.clear();

		char* operation = new char[10];
		std::cout << "Enter operation: ";
		std::cin.getline(operation, 9);
		std::cin.clear();
		db->aggregateTwoRecords(tableName, tableColumnName, tableColumnName, operation, value);

		delete[] operation;
		delete[] targetColumn;
		delete[] value;
		delete[] tableName;
		delete[] tableColumnName;
	}
}

void DatabaseManager::printEnterTableName() const
{
	std::cout << "Enter table name: ";
}

void DatabaseManager::printEnterFileName() const
{
	std::cout << "Enter file name";
}

void DatabaseManager::printEnterValue()
{
	std::cout << "Enter value: ";
}

DatabaseManager::DatabaseManager():db(Database::GetInstance())
{
	
}

Database* DatabaseManager::GetInstance()
{
	if (db == nullptr) 
	{
		
		db=Database::GetInstance();
		return db;
	}
	return db;
}
