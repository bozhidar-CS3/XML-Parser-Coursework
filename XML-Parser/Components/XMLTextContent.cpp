#include "XMLTextContent.h"
#include <iostream>
#include <string>

XMLTextContent::XMLTextContent()
{
	content = "";
}

XMLTextContent::XMLTextContent(const std::string& possible_content)
{
	//Евнтуално проверка за стринга дали е валиден текст ? Може би.
	content = possible_content;
}

const std::string& XMLTextContent::get_content() const
{
	return content;
}

XMLTextContent& XMLTextContent::set_content(const std::string& possible_content)
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

bool XMLTextContent::is_valid_content(const std::string& possible_content) const
{
	if (possible_content.find("<") != std::string::npos || possible_content.find(">") != std::string::npos)
	{
		return false;
	}
	return true;
}
