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
	if (line.find('>', line.find("</")))
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
	unsigned cnt = 0;

	if (check_for_multiple_tags(line))
	{
		size_t pos = 0;
		pos = line.find("</", pos);
		unsigned cnt = 0;
		while (pos != std::string::npos)
		{
			cnt++;
			pos = line.find("</", pos);

		}
	}
	return cnt;


}

std::string XMLCommands::trim(const std::string& raw_text)
{
	size_t actual_start_of_text = raw_text.find_first_not_of(" \n\r\t");
	if (actual_start_of_text == std::string::npos)
	{
		return "";
	}
	else
	{
		size_t end_of_text = raw_text.find_last_not_of(" \n\r\t");
		return raw_text.substr(actual_start_of_text, end_of_text - actual_start_of_text + 1);
	}
}

std::string XMLCommands::get_next_token(std::ifstream& file)
{
	int cur_symbol = file.peek(); // prawim go инт за да може да хване -1 което eof връща.

	while (cur_symbol != EOF && std::isspace(static_cast<unsigned char>(cur_symbol)))  //маха табове, нови редове, интервали. //static_cast<unsigned char>   - Слагаме го за да може да разчита кирилица/
	{
		file.get();
		cur_symbol = file.peek();
	}

	if (cur_symbol == EOF)   //Ако е приключил
	{
		return "";
	}
	if (cur_symbol == '<')
	{
		std::string cur_tag;
		std::getline(file, cur_tag, '>');
		return cur_tag + '>';
	}
	else
	{
		std::string text;
		std::getline(file, text, '<');
		file.putback('<');
		return text;
	}

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

void XMLCommands::fill_attributes(std::string& attribute_text, std::vector<Attribute>& location)
{
	if (attribute_text.length() == 0 || attribute_text.empty() == true)
	{
		return;
	}
	std::string text_copy = attribute_text;
	size_t attribute_name_end, attribute_value_start, attribute_value_end;

	std::string attribute_name;
	std::string attribute_value;
	if (text_copy.find('=') == std::string::npos)
	{
		return;
	}

	attribute_name_end = text_copy.find('=');

	size_t first_quote = text_copy.find('"', attribute_name_end);

	if (first_quote == std::string::npos) return;

	attribute_value_start = first_quote + 1;

	attribute_value_end = text_copy.find('"', attribute_value_start);

	if (attribute_value_end == std::string::npos)
	{
		attribute_value_end = text_copy.length();
	}
	//това ще променяме заради test24.05{

	//size_t space_before_name = text_copy.rfind(' ', attribute_name_end);
	//if (space_before_name == std::string::npos)
	//{
	//	space_before_name = 0;
	//}
	//else
	//{
	//	space_before_name += 1; 
	//}
	//attribute_name = text_copy.substr(space_before_name, attribute_name_end - space_before_name);

	//}


	//Евнтуално да може да има > вътре но това изисква КДТА.
	//нова логика
	std::string name_part = text_copy.substr(0, attribute_name_end);
	size_t actual_end_of_name = name_part.find_last_not_of(" \n\r\t");
	if (actual_end_of_name != std::string::npos)
	{
		size_t  actual_start_of_name = name_part.find_last_of(" \n\r\t<", actual_end_of_name);
		if (actual_start_of_name == std::string::npos)
		{
			actual_start_of_name = 0;
		}
		else
		{
			actual_start_of_name += 1;
		}
		attribute_name = name_part.substr(actual_start_of_name, actual_end_of_name - actual_start_of_name + 1);
	}
	else
	{
		return;
	}


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

	// Ако втората кавичка е била последният символ в стринга, няма какво повече да четем
	if (attribute_value_end + 1 >= text_copy.length())
	{
		return;
	}

	attribute_text = text_copy.substr(attribute_value_end + 1);

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

	std::string tag;
	if (check_for_tags(line) == true)
	{
		//добваяме заради test24,05
		int search_start = 1;
		if (line.length() > 1 && line[1] == '/') search_start = 2;

		size_t end_position = line.find_first_of(" \n\r\t>/", search_start);//добваяме заради test24,05 \t - tab, \r - някакъв ретърн когато сложим ентър.
		if (end_position != std::string::npos)
		{
			tag = line.substr(0, end_position);
		}
		else
		{
			tag = line;
		}


		//tag = line.substr(0, line.find_first_of(" >")); - махаме специално заради test24.05.
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
