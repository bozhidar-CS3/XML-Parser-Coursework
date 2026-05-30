#include "Unique.h"

void UniqueId::fill_unique_ids(const std::string id_value)
{
    unique_ids.push_back(id_value);
}

//Искам да го ползвам в абстрактните класове, но ще стане цикъл....
//Заради това ще се опитам да го наравя само с атрибути.

void UniqueId::reset_id_values()
{
	unique_ids.clear();
}

int UniqueId::check_one_node_for_id(const std::vector<Attribute>& atributes) const
{
	Attribute cur;
	int pos = 0;
	for (unsigned i = 0; i < atributes.size(); i++)
	{
		cur =atributes[i];
		if (cur.get_attribute_name() == "id")
		{
			return i;
		}
	}
	return -1;
}


int UniqueId::check_one_node_for_id(const std::vector<Attribute>& atributes)
{
	Attribute cur;
	int pos = 0;
	for (unsigned i = 0; i < atributes.size(); i++)
	{
		cur = atributes[i];
		if (cur.get_attribute_name() == "id")
		{
			return i;
		}
	}
	return -1;
}
void UniqueId::create_unique_ids(std::vector<Attribute>& atributes, Attribute& unique_id)
{
	int pos = check_one_node_for_id(atributes);
	Attribute cur_attribute;
	if (pos != -1)
	{
		 if (contains_value(atributes[pos].get_attribute_value()))
		 {
			 std::string new_atribute = atributes[pos].get_attribute_value();
			 generate_unique_id(new_atribute);
			 unique_id.set_attribute_name("id");
			 unique_ids.push_back(new_atribute);
			 unique_id.set_attribute_value(new_atribute);
		 }
		 else
		 {
			 unique_id.set_attribute_name("id");
			 unique_ids.push_back(atributes[pos].get_attribute_value());
			 unique_id.set_attribute_value(atributes[pos].get_attribute_value());
		 }
	}
	else
	{
		std::string id_value = "1";
		generate_unique_id(id_value);
		unique_ids.push_back(id_value);
		unique_id.set_attribute_name("id");
		unique_id.set_attribute_value(id_value);
	}
}

bool UniqueId::contains_value(const std::string& value) const
{
	for (std::string i: unique_ids)
	{
		if (i == value)
		{
			return true;
		}
	}
	return false;

}

void UniqueId::generate_unique_id( std::string& value)
{
	int i = 1;
	std::string cur_value;
	char cur_car = '0';
	while (true)
	{
		//cur_car += i; беше така но дава : и тн.
		//cur_value = value + "_" + cur_car;
		cur_value = value + "_" + std::to_string(i);
		if (!contains_value(cur_value))
		{
			value = cur_value;
			return;
		}

		++i;
	}
}
