#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../Components/Attribute.h"
#include "../Components/XMLElementNode.h"
#include"../Components/XMLTextNode.h"
// ../ връща назад

class XMLCommands
{ 
public:
	bool check_for_attribute(const std::string& opening_tag);
	std::string seperate_attributes_from_tag(const std::string&opening_tag);
	void fill_attributes( std::string& attribute_text, std::vector<Attribute>& location);
	std::string remove_tags_from_string(const std::string& line);
	bool check_for_tags(const std::string& line);
	bool check_for_attributes(const std::string& line);
	bool check_for_text_content(const std::string& line);
	void fill_tags(const std::string& line, Tag& destination);
};
