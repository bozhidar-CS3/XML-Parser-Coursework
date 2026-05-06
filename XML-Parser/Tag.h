#pragma once
#include <iostream>
#include <string>
class Tag
{
	std::string opening_tag;
	std::string closing_tag;
public:
	std::string get_opening_tag() const;
	std::string get_closing_tag() const;
	Tag();
	Tag(const std::string);
	bool is_opening_tag_valid(const std::string) const;
};