#pragma once

#include "ShlObj_core.h"
#include <vector>

template< typename T >
class config_item
{
	std::string name;
	T* value;
public:
	config_item(std::string name, T* value)
	{
		this->name = name;
		this->value = value;
	}
};

template< typename T >
class config_value
{
public:
	config_value(std::string name_, T* value_)
	{
		name = name_;
		value = value_;
	}

	std::string name;
	T* value;
};

class c_config_sys
{
protected:
	std::vector< config_value< int >* > ints;
	std::vector< config_value< bool >* > bools;
	std::vector< config_value< float >* > floats;
private:
	void setup_value(int&, int, std::string);
	void setup_value(bool&, bool, std::string);
	void setup_value(float&, float, std::string);
	void setup_value(color&, float, std::string);
public:
	c_config_sys()
	{
		setup();
	}

	void setup();

	void save(std::string config_number);
	void load(std::string config_number);
};

extern c_config_sys* config_system;