#pragma once
#include <vector>
#include <string>
#include "../Components/XMLElementNode.h"
#include "../Components/XMLNode.h"
#include "Unique.h"

class Xpath
{
public:
	void call_the_correct_command(const std::string& user_command);
	XMLNode* get_element_at(const std::vector<XMLNode*>& elements, unsigned position);
	std::vector<Attribute> get_all_attributes_with_name(const std::string& name, const std::vector<XMLNode*>& elements);
	std::vector<XMLNode*> get_element_where_x_is_true(std::vector<XMLNode*> elements, const std::string& child_tag, const std::string& value);
	XMLNode* find_node_by_id(XMLNode* cur_node, const std::string& value);
	Attribute find_attribute(XMLNode* root, const std::string& id_value, const std::string& attribute_name);
	std::string find_attribute_value(XMLNode* root, const std::string& id_value, const std::string& attribute_name);
	void set_attribute_value_by_id(XMLNode*& root, const std::string& id_value, const std::string& attribute_name, const std::string& value);

	std::vector<Attribute>get_children_attributes_by_id(XMLNode* current_node, const std::string& id_value);
	void print_attributes_by_id(XMLNode* current_node, const std::string& id_value);
	
	XMLNode* get_child_at_pos_n(XMLNode* tree,const std::string& id_value, unsigned child_pos);
	void print_child_at_pos_n(XMLNode* tree, const std::string& id_value, unsigned child_pos);

	XMLNode* get_text_node_at_pos_n(XMLNode* tree, const std::string& id_value);
	void print_text_node_at_pos_n(XMLNode* tree, const std::string& id_value);
	bool delete_attribute_by_id(XMLNode* tree, const std::string& id_value, const std::string& key);
	bool add_child_by_id(XMLNode* tree, const std::string& id_value, UniqueId& original);
	void assign_unique_ids(XMLNode* node, UniqueId& id_generator);
protected:
	std::string user_command;
};