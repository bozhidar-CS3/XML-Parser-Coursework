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
	std::string file_path;
	

public:
	bool check_for_attribute(const std::string& opening_tag) const;
	std::string seperate_attributes_from_tag(const std::string& opening_tag);
	void fill_attributes(std::string& attribute_text, std::vector<Attribute>& location);
	std::string remove_tags_from_string(const std::string& line);
	bool check_for_tags(const std::string& line) const;
	bool check_for_attributes(const std::string& line) const;
	bool check_for_text_node(const std::string& line) const;
	void fill_tags(const std::string& line, Tag& destination);
	bool check_for_end_tag(const Tag& tag, const std::string& line) const;
	bool check_for_text_content(const std::string& line) const;
	std::string seperate_text_content(const std::string& line) const;   //seperates text content from the tags and attributes
	//bool check_attribute_for_id(const Attribute& location) const;
	//bool check_for_id_correctnest(const std::vector<Attribute>& location) const;
	void read_from_file(const std::string file_name);


};
