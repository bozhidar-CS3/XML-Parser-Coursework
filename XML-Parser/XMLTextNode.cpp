#include "XMLTextNode.h"
#include <iostream>
#include <string>

XMLTextNode::XMLTextNode()
{
	content = "";
}

XMLTextNode::XMLTextNode(const std::string& possible_content)
{
	//Евнтуално проверка за стринга дали е валиден текст ? Може би.
	content = possible_content;
}

std::string XMLTextNode::get_content() const
{
	return content;
}

XMLTextNode& XMLTextNode::set_content(const std::string& possible_content)
{
	// TODO: //Евнтуално проверка за стринга дали е валиден текст ? Може би.
	if (is_valid_content(possible_content))
	{
		content = possible_content;
	}
	else
	{
		std::cout << "Invalid content! \n";
	}
	return *this;
}

bool XMLTextNode::is_valid_content(const std::string& possible_content) const
{
	if (possible_content.find("<") != std::string::npos || possible_content.find(">") != std::string::npos)
	{
		return false;
	}
	return true;
}
