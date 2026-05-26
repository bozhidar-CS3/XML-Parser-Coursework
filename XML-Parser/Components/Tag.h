#pragma once
#include <iostream>
#include <string>
class Tag
{
	std::string opening_tag;
	std::string closing_tag;
public:
	const std::string& get_opening_tag() const;
	const std::string& get_closing_tag() const;
	void print_tag() const;
	Tag();
	Tag(const std::string&);
	bool is_opening_tag_valid(const std::string&) const;
	Tag& set_tags(const std::string&);

};