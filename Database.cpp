#include "Database.h"


Database* Database::instance = nullptr;

void Database::resize()
{
	Table* otherTable = new Table[this->capacity * 2];
	for (unsigned int i = 0; i < this->size; ++i)
	{
		otherTable[i] = this->tables[i];
	}
	this->capacity *= 2;

	delete[] this->tables;

	this->tables = otherTable;
}

void Database::deleteDynamicMemory()
{
	delete[] this->tables;
	delete Database::instance;
}

Database::Database(unsigned int inputCapacity)
{
	this->capacity = inputCapacity;
	this->size = 0;
	this->tables = new Table[inputCapacity];

}



Database::~Database()
{
	deleteDynamicMemory();
}

int Database::getTableIndexByGivenName(const char* name)
{
	for (unsigned int i = 0; i < this->size; ++i)
	{
		if (strcmp(this->tables[i].getTableName(), name) == 0)
		{
			return i;
		}

	}
	return -1;
}

void Database::loadTable(Table& table)
{
	if (this->size == this->capacity)
	{
		this->resize();
	}
	this->tables[this->size] = table;
	++this->size;
}

bool Database::isTwoTableNamesEquals(const char* tableOneName, const char* TableTwoName)
{
	return false;
}

bool Database::isValidOperation(const char* operation)
{
	if (strcmp(operation, "sum") == 0)
	{
		return true;
	}
	else
		if (strcmp(operation, "product") == 0)
		{
			return true;
		}
		else
			if (strcmp(operation, "maximum") == 0)
			{
				return true;
			}
			else
				if (strcmp(operation, "minimum") == 0)
				{
					return true;
				}
	return false;
}

Database* Database::GetInstance()
{
	if (Database::instance == nullptr)
	{
		Database::instance = new Database();
	}
	return Database::instance;
}



void Database::serialise(std::ofstream& stream) const
{
	if (!stream.is_open())
	{
		return;
	}

	stream.write((const char*)& this->size, sizeof(this->size));
	stream.write((const char*)& this->capacity, sizeof(this->capacity));

	for (unsigned int i = 0; i < this->size; ++i)
	{
		this->tables[i].serialise(stream);
	}

}

void Database::deserialise(std::ifstream& stream)
{
	if (!stream.is_open())
	{
		return;
	}
	if (tables != nullptr)
	{
		delete[] tables;
	}

	stream.read((char*)& this->size, sizeof(this->size));
	stream.read((char*)& this->capacity, sizeof(this->capacity));
	//deleteDynamicMemory();
	this->tables = new Table[this->capacity];

	for (unsigned int i = 0; i < this->size; ++i)
	{
		this->tables[i].deserialise(stream);
	}

}

void Database::addTable()
{

	const unsigned int maxTableNameLength = 100;
	char* tableName = new char[maxTableNameLength];
	std::cout << "Enter Table Name: ";
	std::cin.getline(tableName, maxTableNameLength);
	//std::cin.clear();
	Table t = Table(tableName);
	while (true)
	{
		std::cout << "Would you like to add  field y or n ";
		char command;
		std::cin >> command;
		std::cin.clear();
		std::cin.ignore();
		if (command == 'n')
		{
			break;
		}
		if (command != 'y')
		{
			std::cout << "You enter invalid command" << std::endl;
			return;
		}
		t.addField();




	}
	if (this->size == this->capacity)
	{
		this->resize();
	}
	this->tables[size] = t;
	++this->size;

	delete[] tableName;
}

const unsigned int Database::getSize() const
{
	return this->size;
}

void Database::print(const char* tableName)
{
	int index = this->getTableIndexByGivenName(tableName);

	if (index == -1)
	{
		std::cout << "Invalid table name " << std::endl;
		return;
	}
	tables[index].printTable();
}

void Database::exportTableToFile(const char* tableName, const char* fileName)
{
	int index = this->getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "Table not found " << std::endl;
		return;
	}
	Table& table = this->tables[index];
	std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
	table.serialise(ofs);

	if (ofs.good())
	{
		std::cout << "Table is exported to File:" << fileName << std::endl;
	}
	else
	{
		std::cout << "Export failed" << std::endl;
	}
	ofs.close();
}

void Database::importTableFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (ifs.good())
	{
		Table t = Table();
		t.deserialise(ifs);
		this->loadTable(t);

		if (ifs.good()) {

			std::cout << "Table loaded in Database: " << std::endl;
		}
		else
		{
			std::cout << "Loaded Fail" << std::endl;
		}
	}
	else
	{
		std::cout << "Loaded Fail" << std::endl;
	}

}

void Database::printTableNames() const
{
	for (unsigned int i = 0; i < this->size; ++i)
	{
		std::cout << "Table name: " << this->tables[i].getTableName() << std::endl;
	}
}

void Database::showTableTypes(const char* tableName)
{
	int index = this->getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "Invalid table name " << std::endl;
		return;
	}
	this->tables[index].getFieldType();
}

void Database::selectColumnsByValueAndTableName(const char* tableName, const char* value)
{
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "Incorrect table name " << std::endl;
		return;
	}
	this->tables[index].printFieldByGivenValue(value);

}

void Database::addColumnToTableByGivenName(const char* tableName, const char* columnType, const char* columnName)
{
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}
	this->tables[index].addFieldByGivenNameAndColumnType(columnName, columnType);

}

void Database::updateColumnValue(const char* tableName, const char* columnName, const char* value, const char* targetColumnName, const char* targetColumnValue)
{
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}

}

void Database::deleteColumnsByGivenValue(const char* tableName, const char* columnName, const char* value)
{
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}
	this->tables[index].deleleColumnsBygivenValue(columnName, value);
}

void Database::addColumns(const char* tableName)
{
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}
	char command;
	while (true)
	{
		this->tables[index].addField();

		std::cout << "Would you like to add another field: y or n ";
		std::cin >> command;
		std::cin.clear();
		std::cin.ignore();
		if (command == 'n')
		{
			break;
		}
		if (command != 'y')
		{
			std::cout << "You entered uncorrect command" << std::endl;
			return;
		}
	}

}

void Database::innerJoin(const char* tableOne, const char* tableTwo, const char* tableOneColumn, const char* tableTwoColumn)
{
	int tableIndexOne = this->getTableIndexByGivenName(tableOne);
	if (tableIndexOne == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}

	int tableIndexTwo = this->getTableIndexByGivenName(tableTwo);

	if (tableIndexTwo == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}

	this->tables[tableIndexOne].innerJoin(this->tables[tableIndexTwo], tableTwoColumn);



}

void Database::renameTableName(const char* oldTableName, const char* newTableName)
{
	int index = getTableIndexByGivenName(newTableName);

	if (index != -1)
	{
		std::cout << "There is table with that name " << std::endl;
		return;
	}

	int tableIndex = getTableIndexByGivenName(oldTableName);
	if (tableIndex == -1)
	{
		std::cout << "There is no table with that name" << std::endl;
		return;
	}

	this->tables[tableIndex].setNewTableName(newTableName);

	std::cout << oldTableName << " renamed to " << newTableName << std::endl;
}

void Database::countRecords(const char* tableName, const char* columnName, const char* value)
{

	 
	
	int index = getTableIndexByGivenName(tableName);
	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}
	this->tables[index].countRecordsByGivenValue(columnName, value);


}

void Database::aggregateTwoRecords(const char* tableName, const char* searchColumn, const char* targetColumn, const char* operation,const char* value)
{
	if (!isValidOperation(operation)) 
	{
		std::cout << "Invalid operation" << std::endl;
		return;
	}

	int index = getTableIndexByGivenName(tableName);

	if (index == -1)
	{
		std::cout << "You entered uncorrect table name" << std::endl;
		return;
	}
	tables[index].aggregateBetwenTwoColumn(targetColumn, searchColumn, value, operation);

}
