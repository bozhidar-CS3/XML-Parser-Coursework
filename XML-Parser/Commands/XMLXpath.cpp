#include "XMLXpath.h"
XMLNode* Xpath::get_element_at(const std::vector<XMLNode*>& elements, unsigned position)
{
	if (position >= elements.size())
	{
		return nullptr;
	}
	return elements[position];
}

std::vector<Attribute> Xpath::get_all_attributes_with_name(const std::string& name, const std::vector<XMLNode*>& elements)
{
	std::vector<Attribute> attributes;
	if (name == "id")
	{

		Attribute atr;
		for (XMLNode* i : elements)
		{
			Attribute atr = i->get_id();
			if (atr.get_attribute_value() != "")
			{
				attributes.push_back(atr);
			}
			attributes.push_back(i->get_id());
		}
	}
	else
	{
		for (XMLNode* i : elements)
		{
			std::vector<Attribute> temp = i->get_attributes();
			for (const Attribute& j : temp)
			{
				if (j.get_attribute_name() == name)
				{
					attributes.push_back(j);
					break;
				}
			}
		}
	}

	return attributes;


}

std::vector<XMLNode*> Xpath::get_element_where_x_is_true(std::vector<XMLNode*> elements, const std::string& child_tag, const std::string& value)
{
	std::vector<XMLNode*> result;
	for (XMLNode* i : elements)
	{
		//	i->print(std::cout); std::cout << "\n";
		//	std::cout << child_tag;
		std::vector<XMLNode*> children = i->get_children();
		for (XMLNode* j : children)
		{
			if (j->get_tag_name() == child_tag)
			{
				if (j->get_text_content() == value)
				{
					result.push_back(i);
					break;
				}

			}
		}

	}
	return result;

}

XMLNode* Xpath::find_node_by_id(XMLNode* cur_node, const std::string& value)
{
	if (cur_node == nullptr)
	{
		return nullptr;
	}

	if (cur_node->get_unique_id_value() == value)
	{
		return cur_node;
	}

	std::vector<XMLNode*> children = cur_node->get_children();
	for (XMLNode* i : children)
	{
		XMLNode* cur_child = find_node_by_id(i, value);
		if (cur_child != nullptr)
		{
			return cur_child;
		}
	}
	return nullptr;
}

Attribute Xpath::find_attribute(XMLNode* root, const std::string& id_value, const std::string& attribute_name)
{
	XMLNode* node = find_node_by_id(root, id_value);
	if (node != nullptr)
	{
		for (const Attribute& i : node->get_attributes())
		{
			if (i.get_attribute_name() == attribute_name)
			{
				return i;
			}
		}
	}
	return Attribute();
}

std::string Xpath::find_attribute_value(XMLNode* root, const std::string& id_value, const std::string& attribute_name)
{
	Attribute attribute = find_attribute(root, id_value, attribute_name);//може и без този ред, мислех да го ползвам и за селект и сет, не става
	if (!attribute.is_empty())
	{
		return attribute.get_attribute_value();
	}


	return std::string();
}

void Xpath::set_attribute_value_by_id(XMLNode*& root, const std::string& id_value, const std::string& attribute_name, const std::string& value)
{
	XMLNode* node = find_node_by_id(root, id_value);
	if (node != nullptr)
	{
		node->set_attribute_value(value, attribute_name);
	}

}

std::vector<Attribute> Xpath::get_children_attributes_by_id(XMLNode* current_node, const std::string& id_value)
{
	XMLNode* node = find_node_by_id(current_node, id_value);
	if (node != nullptr)
	{

		std::vector	<XMLNode*> children = node->get_children();
		std::vector<Attribute> children_attributes;
		for (XMLNode* i : children)
		{
			for (const Attribute& j : i->get_attributes())
			{
				children_attributes.push_back(j);
			}
		}
		return children_attributes;
	}


	return std::vector<Attribute>();
}

void Xpath::print_attributes_by_id(XMLNode* current_node, const std::string& id_value)
{
	XMLNode* node = find_node_by_id(current_node, id_value);
	if (node != nullptr)
	{
		std::vector	<XMLNode*> children = node->get_children();

		for (XMLNode* i : children)
		{
			for (const Attribute& j : i->get_attributes())
			{
				std::cout << j.get_attribute_name() << ": " << j.get_attribute_value();
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "NO such id<<\n";
	}
}

XMLNode* Xpath::get_child_at_pos_n(XMLNode* tree, const std::string& id_value, unsigned child_pos)
{
	XMLNode* node = find_node_by_id(tree, id_value);
	if (node != nullptr)
	{

		std::vector<XMLNode*> children = node->get_children();
		if (children.size() > child_pos)
		{
			return children[child_pos];
		}

	}
	return nullptr;
}

void Xpath::print_child_at_pos_n(XMLNode* tree, const std::string& id_value, unsigned child_pos)
{
	XMLNode* node = get_child_at_pos_n(tree, id_value, child_pos);
	if (node != nullptr)
	{
		node->print(std::cout);
	}
}

XMLNode* Xpath::get_text_node_at_pos_n(XMLNode* tree, const std::string& id_value)
{
	XMLNode* node = find_node_by_id(tree, id_value);
	if (node != nullptr && node->get_type() == "TextNode")
	{
		return node;
	}
	return nullptr;
}

void Xpath::print_text_node_at_pos_n(XMLNode* tree, const std::string& id_value)
{
	XMLNode* ptr = get_text_node_at_pos_n(tree, id_value);
	if (ptr != nullptr)
	{
		ptr->print(std::cout);
	}
	std::cout << "";
}

bool Xpath::delete_attribute_by_id(XMLNode* tree, const std::string& id_value, const std::string& key)
{
	XMLNode* node = find_node_by_id(tree, id_value);
	if (node != nullptr)
	{
		node->delete_attribute_by_key(key);
		return true;
	}
	return false;
}

bool Xpath::add_child_by_id(XMLNode* tree, const std::string& id_value, UniqueId& original)
{
	XMLNode* node = find_node_by_id(tree, id_value);
	if (node != nullptr)
	{
		
		std::string id_value1 = "new_node";
		original.generate_unique_id(id_value1);
		original.fill_unique_ids(id_value1);
		Attribute id("id", id_value1);
		XMLElementNode* new_el = new XMLElementNode();
		new_el->set_unique_id(id);
		if (node->newchild(new_el))
		{
			return true;
		}
		else
		{
			delete new_el;
			return	false;
		}
	}
	return false;

}

void Xpath::assign_unique_ids(XMLNode* current_node, UniqueId& id_generator)
{
	if (current_node == nullptr)
	{
		return;
	}
	Attribute generated_id;
	if (current_node->get_type() == "TextNode")
	{
		std::vector<Attribute> empty;
		id_generator.create_unique_ids(empty, generated_id);
		current_node->set_id(generated_id, generated_id.get_attribute_value());
	}
	else
	{
		std::vector<Attribute> atributes = current_node->get_attributes();
		id_generator.create_unique_ids(atributes, generated_id);
		current_node->set_id(generated_id, generated_id.get_attribute_value());
	}
	std::vector<XMLNode*> children = current_node->get_children();
	for (XMLNode* i:children)
	{
		assign_unique_ids(i, id_generator);
	}

}
