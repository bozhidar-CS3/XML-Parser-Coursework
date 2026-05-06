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

std::string XMLTextNode::get_XMLTextNode() const
{
	return content;
}

XMLTextNode& XMLTextNode::set_XMLTextNode(const std::string& possible_content)
{
	// TODO: //Евнтуално проверка за стринга дали е валиден текст ? Може би.

	content = possible_content;
	return *this;
}
