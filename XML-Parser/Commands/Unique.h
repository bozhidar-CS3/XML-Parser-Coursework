#pragma once
#include <vector>
#include <string>
#include "../Components/Attribute.h"

class UniqueId
{
public:
	void reset_id_values();
	int check_one_node_for_id(const std::vector<Attribute>& atributes) const;
	void fill_unique_ids(const std::string id_value);
	int check_one_node_for_id(const std::vector<Attribute>& atributes) ;//Това е за възел без деца.
	void create_unique_ids(std::vector<Attribute>& atributes, Attribute& unique_id);
	bool contains_value(const std::string& value) const;
	void generate_unique_id( std::string& value);
private:
	std::vector<std::string> unique_ids;
};