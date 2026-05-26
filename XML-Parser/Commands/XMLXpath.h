#pragma once
#include <vector>
#include <string>
#include "../Components/XMLElementNode.h"
#include "../Components/XMLNode.h"

class Xpath
{
public:
	void call_the_correct_command(const std::string& user_command);
	XMLNode* get_element_at(const std::vector<XMLNode*>& elements, unsigned position);
	std::vector<Attribute> get_all_attributes_with_name(const std::string& name, const std::vector<XMLNode*>& elements);
	std::vector<XMLNode*> get_element_where_x_is_true(std::vector<XMLNode*> elements, const std::string& child_tag,  std::string& value);

protected:
	std::string user_command;
};