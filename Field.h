#pragma once
#include<fstream>
#pragma warning(disable:4996)

class Field
{
private:
	char* name;
	char* type;
	bool isNullable;
	char* value;
	unsigned int id;
public:
	Field();
	Field(const char* name,const char* type,const char* value,bool isNull,unsigned int id);
	Field& operator=(const Field& other);
	
	~Field();
	void serialise(std::ofstream& stream)const;
	void deserialise(std::ifstream& stream);
	void info();
	const char* getFieldType()const;
	const char* getFieldName()const;
	const char* getFieldValue()const;
	const unsigned int getId()const;
	void setValue(const char* value);
};

