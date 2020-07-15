#pragma once
#include <fstream>
#include<iostream>
#include"Types.h"
#include "Field.h"
#include<cstring>
#include <stdlib.h>
#pragma warning(disable:4996)
class Table
{
private:
	
	char* name;
	Field* fields;
	unsigned int fieldSize;
	unsigned int fieldCapacity;
	
	bool isCorrectFieldType(const char* fieldType);
	bool isValidInt(const char* value);
	bool isValidDouble(const char* value);
	void resize();
	char* parseDoubleToCharArray (double value);
	bool isFieldCorrect(Field& field);
	
public:
	Table();
	Table(const int fieldCapacity);
	Table(const char* name);
	Table(const Table& other);
	~Table();
	Table& operator=(const Table& other);
	void serialise(std::ofstream& stream)const;
	void deserialise(std::ifstream& stream);
	void addField();
	void printTable()const;
	const char* getTableName()const;
	void getFieldType();
	void printFieldByGivenValue(const char* value);
	void addFieldByGivenNameAndColumnType(const char* columnName, const char* columnType);
	void updateValue(const char* columnName, const char* columnValue, const char* targetColumName, const char* targetColumnValue);
	void deleleColumnsBygivenValue(const char* columnName, const char* columnValue);
	void innerJoin(Table& otherTable, const char* otherColumnName);
	void setNewTableName(const char* newName);
	void countRecordsByGivenValue(const char* column, const char* value);
	void aggregateBetwenTwoColumn(const char* tagetColumn, const char* searchColumn, const char* value,const char* operation);
};

