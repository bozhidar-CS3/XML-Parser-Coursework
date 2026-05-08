#pragma once
#include <iostream>
#include <vector>
#include <string>

class Attribute
{
	std::string attribute_name;
	std::string attribute_value;

public:
	bool check_attribute_name(const std::string&) const ;
	Attribute();
	Attribute(const std::string&, const std::string&);
	const std::string& get_attribute_name() const;
	const std::string& get_attribute_value() const;
	Attribute&  set_attribute_value(const std::string& );
	Attribute& set_attribute_name(const std::string&);
};
//Задавам функционалностите, които мисля, че са ми необходими засега.


