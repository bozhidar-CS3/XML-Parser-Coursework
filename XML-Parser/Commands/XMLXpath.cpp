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

std::vector<XMLNode*> Xpath::get_element_where_x_is_true(std::vector<XMLNode*> elements, const std::string& child_tag, std::string& value)
{
	std::vector<XMLNode*> result;

	for (XMLNode* i : elements)
	{
		std::vector<XMLNode*> children = i->get_root_children_with_tag(child_tag);
		for (XMLNode* j : children)
		{
			if (j->get_text_content() == value)
			{
				result.push_back(i);//добавяме родителя
				break;
			}
		}

	}
	return result;

}
