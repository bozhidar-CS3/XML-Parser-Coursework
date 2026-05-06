#include "Attribute.h"
#include <iostream>
#include <string>

bool Attribute::check_attribute_name(const std::string& possible_name) const
{
	if (!possible_name.empty() && possible_name[0] !='<' && possible_name[possible_name.length() - 1] != '>')
	{
		//Тук може да се наложи подобрение в процеса на работа
		return true;
	}
	return false;
}

Attribute::Attribute()
{
	attribute_name = "";
	attribute_value = "";
}

Attribute::Attribute(const std::string& possible_name, const std::string& possible_value)
{
	if (check_attribute_name(possible_name))
	{
		attribute_name = possible_name;
		attribute_value = possible_value;

	}
	else
	{
		std::cout << "Invalid attribute name!\n";
		attribute_name = "";
		attribute_value = "";
		return;
	}

	
}

std::string Attribute::get_attribute_name() const
{
	return attribute_name;
}

std::string Attribute::get_attribute_value() const
{
	return attribute_value;
}

Attribute& Attribute::set_attribute_value(const std::string& possible_value)
{
		attribute_value = possible_value;
		std::cout << "Attribute value set successfully! \n";
	return *this;
}

Attribute& Attribute::set_attribute_name(const std::string& possible_name)
{
	if (check_attribute_name(possible_name))
	{
		attribute_name = possible_name;
		std::cout << "Attribute name set successfully! \n";
	}
	else
	{
		std::cout << "Invalid attribute name!\n";
	}
	return *this;
}
