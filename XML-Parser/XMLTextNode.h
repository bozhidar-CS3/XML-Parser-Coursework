#pragma once
#include <iostream>
#include <string>

class XMLTextNode
{
	std::string content;
public:
	XMLTextNode();
	XMLTextNode(const std::string&);
	std::string get_content() const;
	XMLTextNode& set_content(const std::string&);
	bool is_valid_content(const std::string&) const;
	//Евнтуално за подобрение може да се insert  или add_after/add_at_the_end
};