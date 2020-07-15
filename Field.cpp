#include "Field.h"
#include <iostream>

Field::Field()
{
	this->name = nullptr;
	this->value = nullptr;
	this->type = nullptr;
	this->id = 0;
	this->isNullable = false;
}

Field::Field(const char* name, const char* type,const char* value, bool isNull, unsigned int id)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->type = new char[strlen(type) + 1];
	strcpy(this->type, type);
	this->value = new char[strlen(value) + 1];
	strcpy(this->value, value);
	this->isNullable = isNull;
	this->id = id;
}

Field& Field::operator=(const Field& other)
{
	if (this != &other) 
	{
		delete[] type;
		delete[] name;
		delete[] value;

		this->name = new char[strlen(other.name) + 1];
		strcpy(this->name, other.name);
		this->type = new char[strlen(other.type) + 1];
		strcpy(this->type, other.type);
		this->value = new char[strlen(other.value) + 1];
		strcpy(this->value, other.value);
		this->isNullable = other.isNullable;
		this->id = other.id;
	
	}
	return *this;
}

Field::~Field()
{
	delete[] type;
	delete[] name;
	delete[] value;
}

void Field::serialise(std::ofstream& stream) const
{
	if (!stream.is_open())
	{
		return;
	}
	unsigned int nameLenght = strlen(this->name);
	stream.write((const char*)&nameLenght, sizeof(unsigned int));
	stream.write(this->name, nameLenght * sizeof(char));

	unsigned int typeLenght = strlen(this->type);
	stream.write((const char*)&typeLenght, sizeof(unsigned int));
	stream.write(this->type, typeLenght * sizeof(char));

	unsigned int valueLenght = strlen(this->value);
	stream.write((const char*)&valueLenght, sizeof(unsigned int));
	stream.write(this->value, valueLenght * sizeof(char));

	

	stream.write((const char*)&this->isNullable, sizeof(bool));

	stream.write((const char*)& this->id, sizeof(unsigned int));

	if (stream.good())
		std::cout << "Successfully serialize" << std::endl;
	else
		std::cout << "Serialize failed" << std::endl;
}

void Field::deserialise(std::ifstream& stream)
{
	if (!stream.is_open())
	{
		std::cout << "Serialize failed" << std::endl;
		return;
	}
	
	if (this->name != nullptr) 
	{
		delete[] name;
	}
	unsigned int nameLenght = 0;
	stream.read((char*)&nameLenght, sizeof(nameLenght));
	this->name = new char[nameLenght + 1];
	if (this->name) 
	{
		stream.read(this->name, nameLenght);
		name[nameLenght] = '\0';
	}else
	{
		std::cout << "error while reading File" << std::endl;
		return;
	}

	
	if (this->type != nullptr) 
	{
		delete[] type;
	}
	unsigned int typeLenght = 0;
	stream.read((char*)&typeLenght, sizeof(typeLenght));
	this->type = new char[typeLenght + 1];
	if(this->type)
	{
		stream.read(this->type, typeLenght);
		this->type[typeLenght] = '\0';
	}else
	{
		std::cout << "error while reading File" << std::endl;
		return;
	}
	
	if (this->value != nullptr) 
	{
		delete[] this->value;
	}
	unsigned int valueLenght = 0;
	stream.read((char*)& valueLenght, sizeof(valueLenght));
	this->value = new char[valueLenght + 1];
	if (this->value) 
	{
		stream.read(this->value, valueLenght);
		this->value[valueLenght] = '\0';
	}
	else 
	{
		std::cout << "error while reading File" << std::endl;
		return;
	}

	stream.read((char*)&this->isNullable, sizeof(bool));

	stream.read((char*)&this->id, sizeof(unsigned int));
	
	if (stream.good())
	{
		std::cout << "Successfully deserialize" << std::endl;

	}
	else
	{
		std::cout << "Deserialize failed" << std::endl;

	}



}
void Field::info()
{
	std::cout << "Field id: " << id << std::endl;
	std::cout << "Field IsNullable: " << isNullable << std::endl;
	std::cout << "Field name: " << name << std::endl;
	std::cout << "Field type: " << type << std::endl;
	std::cout << "Field value: " << value << std::endl;


}

const char* Field::getFieldType() const
{
	return this->type;
}

const char* Field::getFieldName() const
{
	return this->name;
}

const char* Field::getFieldValue() const
{
	return this->value;
}

const unsigned int Field::getId() const
{
	return this->id;
}

void Field::setValue(const char* value)
{
	delete[] this->value;
	this->value = new char[strlen(value) + 1];
	strcpy(this->value, value);
}
