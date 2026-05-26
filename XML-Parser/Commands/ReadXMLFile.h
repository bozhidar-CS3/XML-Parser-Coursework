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

	bool opening_tag_closed(const std::string& line);
	bool closing_tag_closed(const std::string& line);
	unsigned closing_members(const std::string& line, unsigned goal);
	bool check_for_multiple_tags(const std::string& line);
	unsigned get_number_of_tags(const std::string& line);


	std::string trim(const std::string& raw_text);

	//TODO функция, която да намира кое се изисква от нас.
	void seperate_tags_from_user_command(const std::string& user_command, std::string& root_tag, std::string& remainig_path);
	std::vector<std::string> get_children_with_child_tag(const std::string& user_command);

	std::string get_next_token(std::ifstream& file);
	bool check_for_attribute(const std::string& opening_tag) const;
	std::string seperate_attributes_from_tag(const std::string& opening_tag);
	void fill_attributes(std::string& attribute_text, std::vector<Attribute>& location);
	std::string remove_tags_from_string(const std::string& line);
	bool check_for_tags(const std::string& line) const;
	bool check_for_attributes(const std::string& line) const;
	 std::string get_next_line();
	 //bool check_for_multiple_tags(const std::string& line) const;
	bool check_for_text_node(const std::string& line) const;
	void fill_tags(const std::string& line, Tag& destination);
	bool check_for_end_tag(const Tag& tag, const std::string& line) const;
	bool check_for_text_content(const std::string& line) const;
	std::string seperate_text_content(const std::string& line) const;   //seperates text content from the tags and attributes
	bool check_for_lonely_end_tag(const std::string& line) const;

	//bool check_attribute_for_id(const Attribute& location) const;
	//bool check_for_id_correctnest(const std::vector<Attribute>& location) const;
	

};
