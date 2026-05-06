#pragma once
#include <iostream>
#include <string>

class XMLTextNode
{
	std::string content;
public:
	XMLTextNode();
	XMLTextNode(const std::string&);
	std::string get_XMLTextNode() const;
	XMLTextNode& set_XMLTextNode(const std::string&);
	//Евнтуално за подобрение може да се insert  или add_after/add_at_the_end
};