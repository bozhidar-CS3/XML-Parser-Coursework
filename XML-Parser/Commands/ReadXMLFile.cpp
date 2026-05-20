#include "ReadXMLFile.h"
#include "../Components/XMLNode.h"
#include <iostream>

bool XMLCommands::opening_tag_closed(const std::string& line)
{
	if (line.find('>') == std::string::npos)
	{
		return false;
	}
	return true;
}

bool XMLCommands::closing_tag_closed(const std::string& line)
{
	if (line.find('>',line.find("</")))
	{
		return true;
	}
	return false;
	
}

unsigned XMLCommands::closing_members(const std::string& line, unsigned goal)
{
	return 0;
}

bool XMLCommands::check_for_multiple_tags(const std::string& line)
{
	size_t first_close = line.find('>');

	if (first_close == std::string::npos)
	{
		return false;
	}

	size_t second_open = line.find('<', first_close);

	

	if (second_open == std::string::npos)
	{
		return false;
	}

	if (second_open + 1 < line.length() && line[second_open + 1] != '/')
	{
		return true;
	}

	return false;
}

unsigned XMLCommands::get_number_of_tags(const std::string& line)
{
	return 0;
}

bool XMLCommands::check_for_attribute(const std::string& opening_tag) const
{
	if (opening_tag.find('=') != std::string::npos)
	{
		return true;
	}
	return false;
}

std::string XMLCommands::seperate_attributes_from_tag(const std::string& opening_tag)
{
	std::string attribute_string;
	size_t attribute_begining;
	attribute_begining = opening_tag.find(' ');
	if (attribute_begining == std::string::npos)
	{
		return "";
	}
	attribute_string = opening_tag.substr(attribute_begining + 1, opening_tag.length() - attribute_begining - 2);
	/*for (size_t i = attribute_begining; i < opening_tag.length() - 1; i++)
	{
		attribute_string[cnt++] += opening_tag[i];
	}*/
	return attribute_string;
}

void XMLCommands::fill_attributes( std::string& attribute_text, std::vector<Attribute>& location)
{
	if (attribute_text.length() == 0 || attribute_text.empty() == true)
	{
		return;
	}
	std::string text_copy = attribute_text;
	size_t attribute_name_end, attribute_value_start, attribute_value_end;
	std::string attribute_name;
	std::string attribute_value;
	attribute_value_start = text_copy.find('=') + 2;
	attribute_name_end = text_copy.find('=');
	attribute_value_end = text_copy.find('"', attribute_value_start);
	if (attribute_value_end == std::string::npos)
	{
		attribute_value_end = text_copy.length();
	}
	attribute_name = text_copy.substr(0, attribute_name_end);
	/*for (size_t i = 0; i < attribute_name_end; i++)
	{
		attribute_name[i] = text_copy[i];
	}*/
	int cnt = 0;
	attribute_value = text_copy.substr(attribute_value_start, attribute_value_end - attribute_value_start);
	/*for (size_t i = attribute_value_start; i < attribute_value_end; i++)
	{
		attribute_value[cnt++] = text_copy[i];
	}*/
	location.push_back(Attribute(attribute_name, attribute_value));
	text_copy.clear();
	text_copy = attribute_text.substr(attribute_value_end + 1, attribute_text.length() - attribute_value_end);
	/*for (size_t i = 0; i < attribute_text.length() - attribute_value_end; i++)
	{
		text_copy[i] = attribute_text[attribute_value_end + i];
	}*/
	attribute_text = text_copy;
	fill_attributes(attribute_text, location);
}

std::string XMLCommands::remove_tags_from_string(const std::string& line)
{
	std::string result;
	size_t result_end = line.find_first_of(" >") - 1;
	result = line.substr(1, result_end);
	return result;
}

bool XMLCommands::check_for_tags(const std::string& line) const 
{
	if (line.find_first_of("<>") != std::string::npos)
	{
		return true;
	}
	return false;
}

bool XMLCommands::check_for_attributes(const std::string& line) const 
{
	if (check_for_tags(line))
	{
		if (line.find(' ') < line.find('>'))
		{
			return true;
		}
	}
	return false;
}

 std::string XMLCommands::get_next_line()
{
	//TODO fix this
	return "new line";
}

 //bool XMLCommands::check_for_multiple_tags(const std::string& line) const
 //{
	// std::string new_line = line.substr(line.find('>'))
	// return false;
 //}

bool XMLCommands::check_for_text_node(const std::string& line) const 
{
	if (check_for_tags(line) == false && line.empty() != true)
	{
		return true;
	}
	return false;
}

std::string XMLCommands::seperate_text_content(const std::string& line) const
{
		return line.substr(line.find('>') + 1, line.rfind('<') - line.find('>'));
}

bool XMLCommands::check_for_lonely_end_tag(const std::string& line) const
{
	if (line.find("</") != std::string::npos)
	{
		return true;
	}
	return false;

}

void XMLCommands::fill_tags(const std::string& line, Tag& destination)
{
	if (check_for_tags(line) == true)
	{
		std::string tag;
		tag = line.substr(0, line.find_first_of(" >"));
		if (tag.back() != '>')
		{
			tag += '>';
		}
		destination.set_tags(tag);
	}
}

bool XMLCommands::check_for_end_tag(const Tag& tag, const std::string& line) const
{
	if (line.find(tag.get_closing_tag()) != std::string::npos)
	{
		return true;
	}
	return false;
}

bool XMLCommands::check_for_text_content(const std::string& line) const
{
	if (line.find('>') + 1 == line.rfind('<'))
	{
		return false;
	}
	return true;
}

//void XMLCommands::read_from_file(const std::string file_name)
//{
//	std::vector<XMLNode*> tree;
//	XMLNode* position;
//	std::ifstream file(file_name);
//	if (!file.is_open())
//	{
//		std::cout << "Can't open the file";
//		return;
//	}
//	std::string line;
//	while (std::getline(file, line))
//	{
//		if (check_for_text_node(line))
//		{
//			//Искм тук да сложа елемент от тип текст възел
//			position->
//		}
//		if (check_for_tags(line))
//		{
//			if (check_for_attribute(line))
//			{
//				position
//			}
//		}
//
//	}
//
//	file.close();
//}

//bool XMLCommands::check_attribute_for_id(const Attribute& location) const
//{
//	if (location.get_attribute_name() == "id")
//	{
//		return true;
//	}
//	return false;
//}
//
//bool XMLCommands::check_for_id_correctnest(const std::vector<Attribute>& location) const
//{
//	std::vector<std::string> values;
//	for (const Attribute attribute:location)
//	{
//		if (!check_attribute_for_id(attribute))
//		{
//			return false;
//		}
//		if (values.size() == 0)
//		{
//			values.push_back(attribute.get_attribute_value());
//		}
//		else
//		{
//			for (std::string value : values)
//			{
//				if (value == attribute.get_attribute_value())
//				{
//					return false;
//				}
//			}
//			values.push_back(attribute.get_attribute_value());
//		}
//	}
//	return true;
//}
