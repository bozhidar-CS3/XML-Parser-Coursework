#include "Tag.h"
#include <iostream>
#include <string>


Tag::Tag()
{
	opening_tag = "";
	closing_tag = "";
}


Tag::Tag(const std::string& potenial_tag)
{
	if (is_opening_tag_valid(potenial_tag))
	{
		opening_tag = potenial_tag;
		closing_tag= potenial_tag;
		closing_tag.insert(1, "/");
		std::cout << "Tags set successfully \n";

	}
	else
	{
		std::cout << "Invalid tag!\n";
	}
}

bool Tag::is_opening_tag_valid(const std::string& potenial_tag) const
{
	if (!potenial_tag.empty() && potenial_tag[0] == '<' && potenial_tag[potenial_tag.length() - 1] == '>')
	{
		return true;
	}
	return false;
}

Tag& Tag::set_tags(const std::string& possible_tag)
{
	if (is_opening_tag_valid(possible_tag))
	{
		opening_tag = possible_tag;
		closing_tag = opening_tag;
		closing_tag.insert(1, "/");
		std::cout << "Tags set successfully \n";
	}
	else
	{
		std::cout << "Invalid tag! \n";
	}

	return *this;
}

const std::string& Tag::get_opening_tag() const
{
	return opening_tag;
}

const std::string& Tag::get_closing_tag() const
{
	return closing_tag;
}