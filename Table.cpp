#include "Table.h"

bool Table::isCorrectFieldType(const char* fieldType)
{
	if (strcmp(fieldType, "integer") == 0) 
	{
		return true;
	}
	if (strcmp(fieldType, "double") == 0)
	{
		return true;
	}
	if (strcmp(fieldType, "text") == 0)
	{
		return true;
	}
	return false;
}

bool Table::isValidInt(const char* value)
{
	for (size_t i = 0; i < strlen(value); i++)
	{
		if (value[i] < 48 || value[i]>57)
		{
			if (i == 0 && value[i] == '-') 
			{
				continue;
			}
			return false;
		}
	}
	return true;
}

bool Table::isValidDouble(const char* value)
{
	double const epsion = 0.001;
	double doubleValue = atof(value);
	if (std::abs(doubleValue - 0.00) < epsion && (strcmp(value,"0.00")==0)) 
	{
		return true;
	}
	if (std::abs(doubleValue - 0.00) < epsion) 
	{
		return false;
	}
	return true;
	
}

void Table::resize()
{
	Field* newFields = new Field[this->fieldCapacity * 2];
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		newFields[i] = fields[i];
	}
	this->fieldCapacity *= 2;
	delete[] this->fields;
	this->fields = newFields;
}

char* Table::parseDoubleToCharArray(double value)
{
	char* charValue = new char[20];
	char* n = new char[5];

	int diff = (int)(value - (int)value) * 100;
	itoa(diff, n, 10);
	itoa((int)value, charValue, 10);

	strcat(charValue, ".");
	strcat(charValue, n);
	delete[] n;
	return charValue;
}

bool Table::isFieldCorrect(Field& field)
{

	for (size_t i = 0; i < this->fieldSize; i++)
	{
		if (strcmp(this->fields[i].getFieldName(), field.getFieldName()) == 0
			&& strcmp(this->fields[i].getFieldType(), field.getFieldType()) != 0) 
		{
			return false;
		}
	}
	return true;
}



Table::Table()
{
	this->name = new char[1];
	strcpy(this->name, "");
	this->fieldCapacity = 8;
	this->fields = new Field[this->fieldCapacity];
	this->fieldSize = 0;
	
	
}

Table::Table(const int fieldCapacity)
{
	this->name = new char[1];
	strcpy(this->name, "");
	this->fieldCapacity = fieldCapacity;
	this->fields = new Field[this->fieldCapacity];
	this->fieldSize = 0;
}

Table::Table(const char* name)
{
	this->name = new char[strlen(name) + 1];
	
	strcpy(this->name, name);
	this->fieldCapacity = 8;
	this->fields = new Field[fieldCapacity];
	this->fieldSize = 0;
	
	
}

Table::Table(const Table& other)
{
	if (this != &other) 
	{
		this->name = new char[ strlen(other.name) +1];
		strcpy(this->name, other.name);
		this->fieldSize = other.fieldSize;
		this->fieldCapacity = other.fieldCapacity;
		this->fields = new Field[other.fieldCapacity];
		for (size_t i = 0; i < other.fieldSize; ++i)
		{
			this->fields[i] = other.fields[i];
		}
		
	}else
	{
		this->name = new char[1];
		strcpy(this->name, "");
		this->fieldCapacity = 8;
		this->fieldSize = 0; \
		this->fields = new Field[this->fieldCapacity];
	}
}

Table::~Table()
{
	delete[] this->name;
	delete[] this->fields;
	
}

Table& Table::operator=(const Table& other)
{
	if (this != &other) 
	{
		delete[] name;
		delete[] fields;

		this->name = new char[strlen(other.name) + 1];
		strcpy(this->name, other.name);
		this->fieldCapacity = other.fieldCapacity;
		this->fieldSize = other.fieldSize;
		this->fields = new Field[this->fieldCapacity];
		for (unsigned int i = 0; i < this->fieldSize; ++i)
		{
			this->fields[i] = other.fields[i];
		}
		
	}
	return *this;
	
}

void Table::serialise(std::ofstream& stream) const
{

	if(!stream.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	unsigned int lenghtTableName = strlen(this->name);
	stream.write((const char*)&lenghtTableName, sizeof(lenghtTableName));
	stream.write(this->name, lenghtTableName*sizeof(char));
	
	stream.write((const char*)&this->fieldCapacity, sizeof(unsigned int));
	stream.write((const char*)&this->fieldSize, sizeof(unsigned int));
	
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		this->fields[i].serialise(stream);
	}



}

void Table::deserialise(std::ifstream& stream)
{
	if (!stream.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	
	unsigned int tableLenght = 0;
	stream.read((char*)& tableLenght, sizeof(tableLenght));

	if (this->name != nullptr) {
		delete[] this->name;
	}

	this->name = new char[tableLenght + 1];

	if (this->name)
	{
		stream.read(this->name, tableLenght);
		this->name[tableLenght] = '\0';
	}
	else
	{
		std::cout << "error while reading File" << std::endl;
		return;

	}
	

	stream.read((char*)&this->fieldCapacity, sizeof(fieldCapacity));
	stream.read((char*)&this->fieldSize, sizeof(fieldSize));
	
	
	if (fields != nullptr) 
	{
		delete[] fields;
	}

	this->fields = new Field[this->fieldCapacity];
	
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		fields[i].deserialise(stream);
	}

	if (stream.good()) 
	{
		std::cout << "Successfully deserialize" << std::endl;
	
	}else
	{
		std::cout << "Deserialize failed" << std::endl;
	
	}



}

void Table::addField()
{
	if (this->fieldSize == this->fieldCapacity) 
	{
		this->resize();
	}
	std::cout << "Enter field type(integer,double or text): ";
	char* fieldType = new char[20];
	std::cin.getline(fieldType,19);
	fieldType[strlen(fieldType) + 1] = '\0';
	std::cin.clear();
	if (!isCorrectFieldType(fieldType)) 
	{
		std::cout << "You enter uncorrect type " << std::endl;
		delete[] fieldType;
		return;
	}
	char* fieldName = new char[255];
	std::cout << "Enter Field Name: ";
	std::cin.getline(fieldName, 254);
	std::cin.clear();
	std::cout << "is field nullable y or n: ";
	char nullable;
	std::cin >> nullable;
	std::cin.clear();
	std::cin.ignore();

	bool isNullable = false;
	if(nullable=='y')
	{
		isNullable = true;
	}
	char command;
	char* fieldValue = new char[256];
	
	if (isNullable) 
	{
		std::cout << "field is nullable would you like to enter value y or n: ";
		std::cin >> command;
		std::cin.clear();
		std::cin.ignore();

		if(command=='y')
		{
			std::cout << "Enter value: ";
			std::cin.getline(fieldValue, 255);
			std::cin.clear();
			if (strcmp(fieldType, "integer")==0) 
			{
				if (!isValidInt(fieldValue)) 
				{
					std::cout << "You enter uncorrect value " << std::endl;
					delete[] fieldType;
					delete[] fieldValue;
					delete[] fieldName;
					return;
				}
				char signedInt;
				std::cout << "signed y or n: ";
				std::cin >> signedInt;
				std::cin.clear();
				std::cin.ignore();
				if (signedInt == 'y') 
				{
					
					
					if (atoi(fieldValue) > 0) 
					{
						char* signedValue = new char[strlen(fieldValue) + 2];

						signedValue[0] = '+';
						for (size_t i = 1; i < strlen(fieldValue)+1; i++)
						{
							signedValue[i] = fieldValue[i - 1];
						}
						signedValue[strlen(fieldValue)+1] = '\0';
						delete[] fieldValue;
						fieldValue = signedValue;
					}
				}
				else if (signedInt == 'n') 
				{
					if (atoi(fieldValue)<0) 
					{
						char* signedValue = new char[strlen(fieldValue) -1];

						for (unsigned int i = 0; i < strlen(fieldValue)-1; i++)
						{
							signedValue[i] = fieldValue[i + 1];
						}
						signedValue[strlen(fieldValue) - 1]='\0';
						delete[] fieldValue;
						fieldValue = signedValue;
					}
				}
				else
				{
					std::cout << "You enter uncorrect command " << std::endl;
					delete[] fieldValue;
					delete[] fieldType;
					delete[] fieldName;
					return;
				}


			}
			else if (strcmp(fieldType, "double") == 0) 
			{
				

				if (!isValidDouble(fieldValue)) 
				{
					std::cout << "You enter uncorrect value " << std::endl;
					delete[] fieldType;
					delete[] fieldValue;
					return;
				}
				char signedDouble;
				std::cout << "signed y or n: ";
				std::cin >> signedDouble;
				std::cin.clear();
				std::cin.ignore();
				if (signedDouble == 'y') 
				{
					
					
					if (atof(fieldValue) > 0.00)
					{
						char* signedValue = new char[strlen(fieldValue) + 2];

						signedValue[0] = '+';
						for (size_t i = 1; i < strlen(fieldValue)+1; i++)
						{
							signedValue[i] = fieldValue[i - 1];
						}
						signedValue[strlen(fieldValue) + 1] = '\0';
						delete[] fieldValue;
						fieldValue = signedValue;
					}
				}
				else if (signedDouble == 'n') 
				{
					if (atoi(fieldValue) < 0.00)
					{
						char* signedValue = new char[strlen(fieldValue) - 1];

						for (unsigned int i = 0; i < strlen(fieldValue) - 1; i++)
						{
							signedValue[i] = fieldValue[i + 1];
						}
						signedValue[strlen(fieldValue) - 1] = '\0';
						delete[] fieldValue;
						fieldValue = signedValue;
					}
				}
				else 
				{
					std::cout << "You enter uncorrect command " << std::endl;
					delete[] fieldValue;
					delete[] fieldType;
					return;
				}

			
			}
			


		}
		else if(command=='n')
		{	
		strcpy(fieldValue, "Null");
		}
		else
		{
		std::cout << "You enter uncorrect command " << std::endl;
		delete[] fieldType;
		delete[] fieldName;
		delete[] fieldValue;
		return;
		}
	}
	else 
	{
	std::cout << "Enter value: ";
	std::cin.getline(fieldValue, 255);
	std::cin.clear();
	if (strcmp(fieldType, "integer") == 0) 
	{
		if (!isValidInt(fieldValue)) 
		{
			std::cout << "You enter uncorrect value " << std::endl;
			delete[] fieldType;
			delete[] fieldValue;
			delete[] fieldName;
			return;
		}

		char signedInt;
		std::cout << "signed y or n: ";
		std::cin >> signedInt;
		std::cin.clear();
		std::cin.ignore();
		if (signedInt == 'y')
		{
			char* signedValue = new char[strlen(fieldValue) + 2];
			
			if (atoi(fieldValue) > 0)
			{
				signedValue[0] = '+';
				for (size_t i = 1; i < strlen(fieldValue)+1; i++)
				{
					signedValue[i] = fieldValue[i - 1];
				}
				signedValue[strlen(fieldValue) + 1] = '\0';
				delete[] fieldValue;
				fieldValue = signedValue;
			}
		}
		else if (signedInt == 'n')
		{
			if (atoi(fieldValue) < 0)
			{
				char* signedValue = new char[strlen(fieldValue) - 1];

				for (unsigned int i = 0; i < strlen(fieldValue) - 1; i++)
				{
					signedValue[i] = fieldValue[i + 1];
				}
				signedValue[strlen(fieldValue) - 1] = '\0';
				delete[] fieldValue;
				fieldValue = signedValue;
			}
		}
		else
		{
			std::cout << "You enter uncorrect command " << std::endl;
			delete[] fieldValue;
			delete[] fieldType;
			delete[] fieldName;
			return;
		}


	}
	else if (strcmp(fieldType, "double") == 0) 
	{
		
		if (!isValidDouble(fieldValue))
		{
			std::cout << "You enter uncorrect value " << std::endl;
			delete[] fieldType;
			delete[] fieldValue;
			return;
		}
		char signedDouble;
		std::cout << "signed y or n: ";
		std::cin >> signedDouble;
		std::cin.clear();
		std::cin.ignore();
		if (signedDouble == 'y')
		{
			
			if (atof(fieldValue) > 0.00)
			{
				char* signedValue = new char[strlen(fieldValue) + 2];
				signedValue[0] = '+';
				for (unsigned int i = 1; i < strlen(fieldValue)+1; ++i)
				{
					signedValue[i] = fieldValue[i - 1];
				}
				signedValue[strlen(fieldValue) + 1] = '\0';
				delete[] fieldValue;
				fieldValue = signedValue;
			}
		}
		else if (signedDouble == 'n')
		{
			if (atoi(fieldValue) < 0.00)
			{
				
				char* signedValue = new char[strlen(fieldValue)-1];

				for (unsigned int i = 0; i < strlen(fieldValue) - 1; ++i)
				{
					signedValue[i] = fieldValue[i + 1];
				}
				signedValue[strlen(fieldValue) - 1] = '\0';
				delete[] fieldValue;
				fieldValue = signedValue;
			}
		}
		else
		{
			std::cout << "You enter uncorrect command " << std::endl;
			delete[] fieldValue;
			delete[] fieldType;
			return;
		}
	}

	}
	std::cout << "Enter column id"; 
	unsigned int id;
	std::cin >> id;
	std::cin.clear();
	std::cin.ignore();
	
	
	Field f = Field(fieldName, fieldType, fieldValue, isNullable, id);

	if (isFieldCorrect(f)) 
	{
		this->fields[this->fieldSize] = f;
		++this->fieldSize;
		std::cout << "Field added succesfully" << std::endl;
		
	}
	else 
	{
		std::cout << "Field is  uncorrect" << std::endl;
	}
	
	delete[] fieldName;
	delete[] fieldType;
	delete[] fieldValue;
}

void Table::printTable() const
{
	std::cout << "Table Name: " << this->name << std::endl;
	for (size_t i = 0; i < this->fieldSize; i++)
	{
		this->fields[i].info();
	}
}

const char* Table::getTableName() const
{
	return this->name;
}

void Table::getFieldType()
{
	std::cout << "table name:" << this->name << std::endl;
	std::cout << "fields:" << std::endl;
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		std::cout << "field name: " << this->fields[i].getFieldName() << " field type: " << this->fields[i].getFieldType()<<std::endl;
	}
}

void Table::printFieldByGivenValue(const char* value)
{
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		if (strcmp(this->fields[i].getFieldValue(), value) == 0) 
		{
			std::cout << "Select query result:" << std::endl;

			std::cout << "Field id:-> " << this->fields[i].getId() << std::endl;
			std::cout << "Field name:-> " << this->fields[i].getFieldName() << std::endl;
			std::cout << "Field value:-> " << value << std::endl;
			for (unsigned int j = 0; j < this->fieldSize; ++j)
			{
				if (i == j) 
				{
					continue;
				}

				if (this->fields[j].getId() != this->fields[i].getId()) 
				{
					continue;
				}


				std::cout << "Field name: " << this->fields[j].getFieldName()<<std::endl;
				std::cout << "Field value: " << this->fields[j].getFieldValue() << std::endl;

			}
		}
	}
}

void Table::addFieldByGivenNameAndColumnType(const char* columnName, const char* columnType)
{
	if (!isCorrectFieldType(columnType)) 
	{
		std::cout << "You enter uncorrect type " << std::endl;
		return;
	}
	
	Field f =Field(columnName,columnType,"Null", true, 0);
	if (this->fieldSize == this->fieldCapacity) 
	{
		this->resize();
	}
	this->fields[this->fieldSize] = f;

	++this->fieldSize;

	std::cout << "You added new column to this table" << std::endl;
}

void Table::updateValue(const char* columnName, const char* columnValue, const char* targetColumName, const char* targetColumnValue)
{
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		if (strcmp(this->fields[i].getFieldName(), columnName) == 0 && strcmp(this->fields[i].getFieldValue(),columnValue)==0) 
		{
		
		}
	}

}

void Table::deleleColumnsBygivenValue(const char* columnName, const char* columnValue)
{
	Field* newFields = new Field[this->fieldCapacity];
	unsigned int newFieldsSize = 0;

	for (unsigned int i = 0; i < this->fieldSize; i++)
	{
		if (strcmp(columnName, this->fields[i].getFieldName()) == 0 && strcmp(columnValue, this->fields[i].getFieldValue()) == 0) 
		{
			continue;
		}
		newFields[i] = this->fields[i];
		++newFieldsSize;
	}

	delete[] this->fields;
	this->fields = newFields;
	std::cout << "Deleted " << this->fieldSize - newFieldsSize << " records"<<std::endl;
	this->fieldSize = newFieldsSize;
}

void Table::innerJoin(Table& otherTable, const char* otherColumnName)
{
	Table newTable = Table(this->fieldCapacity+otherTable.fieldCapacity);

	for (size_t i = 0; i < this->fieldSize; ++i)
	{
		if (strcmp(otherColumnName, this->fields[i].getFieldName()) == 0) 
		{
			newTable.fields[newTable.fieldSize] = this->fields[i];
			++newTable.fieldSize;
		}
	}
	for (size_t i = 0; i < otherTable.fieldSize; ++i)
	{
		if (strcmp(otherColumnName, otherTable.fields[i].getFieldName()) == 0)
		{
			newTable.fields[newTable.fieldSize] = this->fields[i];
			++newTable.fieldSize;
		}
	}
	if (newTable.fieldSize > 0) 
	{

		std::cout << "Inner join found export new Table to File "<<std::endl;
		char* newTableFileName = new char[200];
		strcat(newTableFileName, this->name);
		strcat(newTableFileName, "-");
		strcat(newTableFileName, otherTable.name);

		delete[] newTable.name;
		newTable.name = new char[strlen(newTableFileName) + 1];
		strcpy(newTable.name, newTableFileName);

		strcat(newTableFileName, ".bin");

		std::ofstream ofs(newTableFileName, std::ios::binary | std::ios::out);
		newTable.serialise(ofs);

		if (ofs.good())
		{
			std::cout << "Table is exported to File:" << newTableFileName << std::endl;
		}
		else
		{
			std::cout << "Export failed" << std::endl;
		}
		ofs.close();

		delete[] newTableFileName;

		

		
	}else
	{
		std::cout << "Inner join not found" << std::endl;
	
	}
}

void Table::setNewTableName(const char* newName)
{
	delete[] this->name;
	this->name = new char[strlen(newName) + 1];
	strcpy(this->name, newName);

}

void Table::countRecordsByGivenValue(const char* column, const char* value)
{
	int count = 0;
	for (size_t i = 0; i < this->fieldSize; i++)
	{
		if (strcmp(this->fields[i].getFieldName(), column) == 0 && strcmp(this->fields[i].getFieldValue(),value)==0) 
		{
			++count;
		}
	}
	std::cout << "There are " << count << " records with that value";
}

void Table::aggregateBetwenTwoColumn(const char* tagetColumn, const char* searchColumn, const char* value,const char* operation)
{

	int searcholumnIndex = -1;
	
	for (unsigned int i = 0; i < this->fieldSize; ++i)
	{
		if (strcmp(searchColumn, this->fields[i].getFieldName()) == 0 && strcmp(value,this->fields[i].getFieldValue())==0) 
		{
			
			if (strcmp(this->fields[i].getFieldType(), "text") == 0) 
			{
				std::cout << "Uncorrect column type" << std::endl;
				return;
			}
			searcholumnIndex = i;
			break;
		}
	}
	if (searcholumnIndex == -1) 
	{
		std::cout << "no such column" << std::endl;
		return;
	}

	for (size_t i = 0; i <this->fieldSize; ++i)
	{
		if (strcmp(this->fields[i].getFieldName(), tagetColumn) == 0) 
		{
			if (strcmp(this->fields[i].getFieldType(), "text") == 0)
			{
				std::cout << "Uncorrect column type" << std::endl;
				return;
			}

			if (isValidInt(this->fields[i].getFieldValue())) 
			{
				if (strcmp(operation, "sum") == 0) 
				{
					int value = atoi(this->fields[i].getFieldValue());
					value += atoi(this->fields[searcholumnIndex].getFieldValue());
					char* charValue = new char[20];
					itoa(value, charValue, 10);
					this->fields[i].setValue(charValue);
					delete[] charValue;
				}else
					if (strcmp(operation, "product") == 0)
				{
					int value = atoi(this->fields[i].getFieldValue());
					value *= atoi(this->fields[searcholumnIndex].getFieldValue());
					char* charValue = new char[20];
					itoa(value, charValue, 10);
					this->fields[i].setValue(charValue);
					delete[] charValue;
				}else if (strcmp(operation, "minimum") == 0)
				{

					int targetValue = atoi(this->fields[i].getFieldValue());
					int searchValue = atoi(this->fields[searcholumnIndex].getFieldValue());
					char* charValue = new char[20];
					if (targetValue > searchValue) 
					{
						itoa(searchValue, charValue, 10);
					}
					else if (targetValue < searchValue) 
					{
						itoa(targetValue, charValue, 10);

					}
					else 
					{
						delete[] charValue;
						continue;
					}

					this->fields[i].setValue(charValue);
					delete[] charValue;
				}
				else if (strcmp(operation, "maximum") == 0) 
					{
						int targetValue = atoi(this->fields[i].getFieldValue());
						int searchValue = atoi(this->fields[searcholumnIndex].getFieldValue());
						char* charValue = new char[20];
						if (targetValue > searchValue)
						{
							itoa(targetValue, charValue, 10);
						}
						else if (targetValue < searchValue)
						{
							itoa(searchValue, charValue, 10);

						}
						else 
						{
							delete[] charValue;
							continue;
						}
						this->fields[i].setValue(charValue);
						delete[] charValue;
					}

			}
			else 
			{
				if(strcmp(operation, "sum") == 0) 
				{

					double targetValue = atof(this->fields[i].getFieldValue());
					double searchValue = atof(this->fields[searcholumnIndex].getFieldValue());
					targetValue += searchValue;

					char* charValue = parseDoubleToCharArray(targetValue);
					
					this->fields[i].setValue(charValue);
					delete[] charValue;
					
				}
				else if (strcmp(operation, "product") == 0) 
				{
					double targetValue = atof(this->fields[i].getFieldValue());
					double searchValue = atof(this->fields[searcholumnIndex].getFieldValue());
					targetValue *= searchValue;
					char* charValue = parseDoubleToCharArray(targetValue);
					
					this->fields[i].setValue(charValue);
					delete[] charValue;
					
				}
				else if (strcmp(operation, "minimum") == 0)
				{

					double targetValue = atof(this->fields[i].getFieldValue());
					double searchValue = atof(this->fields[searcholumnIndex].getFieldValue());
					char* charValue=nullptr;
					
					
					if (targetValue > searchValue)
					{
						charValue = parseDoubleToCharArray(searchValue);
					}
					else if (targetValue < searchValue)
					{
						charValue = parseDoubleToCharArray(targetValue);
					}
					else
					{
						
						continue;
					}
					this->fields[i].setValue(charValue);
					delete[] charValue;
					
				}
				else if (strcmp(operation, "maximum") == 0)
				{
					double targetValue = atof(this->fields[i].getFieldValue());
					double searchValue = atof(this->fields[searcholumnIndex].getFieldValue());
					char* charValue=nullptr;
					if (targetValue > searchValue)
					{
						charValue = parseDoubleToCharArray(targetValue);
						
					}
					else if (targetValue < searchValue)
					{
						charValue = parseDoubleToCharArray(searchValue);
					}
					else 
					{
						continue;
					}
					this->fields[i].setValue(charValue);
					delete[] charValue;
					
				}
			
			}

		}
	}


}
