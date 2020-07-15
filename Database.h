#pragma once
#include"Table.h"
#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

class Database
{
private:
	static Database* instance;
	Table* tables;
	unsigned int capacity;
	unsigned int size;
	void resize();
	void deleteDynamicMemory();
	Database(unsigned int inputCapacity = 8);
	~Database();
	int getTableIndexByGivenName(const char* name);
	void loadTable(Table& table);
	bool isTwoTableNamesEquals(const char* tableOneName, const char* TableTwoName);
	bool isValidOperation(const char* operation);
public:
	static Database* GetInstance();
	Database(const Database& other)=delete;
	Database& operator=(const Database& other)=delete;
	void serialise(std::ofstream& stream)const;
	void deserialise(std::ifstream& stream);
	void addTable();
	const unsigned int getSize()const;
	void print(const char* tableName);
	void exportTableToFile(const char* tableName, const char* fileName);
	void importTableFromFile(const char* fileName);
	void printTableNames()const;
	void showTableTypes(const char* tableName);
	void selectColumnsByValueAndTableName(const char* tableName, const char* value);
	void addColumnToTableByGivenName(const char* tableName, const char* columnType, const char* columnName);
	void updateColumnValue(const char* tableName, const char* columnName, const char* value, const char* targetColumnName, const char* targetColumnValue);
	void deleteColumnsByGivenValue(const char* tableName, const char* columnName, const char* value);
	void addColumns(const char* tableName);
	void innerJoin(const char* tableOne, const char* tableTwo, const char* tableOneColumn, const char* tableTwoColumn);
	void renameTableName(const char* oldTableName, const char* newTableName);
	void countRecords(const char* tableName, const char* columnName, const char* value);
	void aggregateTwoRecords(const char* tableName, const char* searchColumn, const char* targetColumn, const char* operation,const char* value);
};
