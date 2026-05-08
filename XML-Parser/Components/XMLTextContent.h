#pragma once
#include <iostream>
#include <string>

class XMLTextContent
{
	std::string content;
public:
	XMLTextContent();
	XMLTextContent(const std::string&);
	const std::string& get_content() const;
	XMLTextContent& set_content(const std::string&);
	bool is_valid_content(const std::string&) const;
	//Евнтуално за подобрение може да се insert  или add_after/add_at_the_end

	//Накрая още проверки за констове и тн.
};