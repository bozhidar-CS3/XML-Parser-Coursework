#include "XMLElementNode.h"
#include <string>

XMLElementNode::XMLElementNode()
{

}

XMLElementNode::~XMLElementNode()
{
	for (size_t i = 0; i < element_children.size(); i++)
	{
		delete element_children[i];
	}
	element_children.clear();
}

const std::string XMLElementNode::get_string() const
{
	return "Id " + unique_id.get_attribute_name() + " " + unique_id.get_attribute_value() + " " + element_tag.get_opening_tag();
}

const Attribute& XMLElementNode::get_unique_id() const
{
	return unique_id;
}

XMLElementNode& XMLElementNode::set_unique_id(const Attribute& id)
{
	unique_id = id;
	return *this;
}

const Tag& XMLElementNode::get_element_tag() const
{
	return element_tag;

}

XMLElementNode& XMLElementNode::set_element_tag(const Tag& tag)
{
	element_tag = tag;
	return *this;
}

const Attribute& XMLElementNode::get_attribute_at(unsigned position) const
{
	return element_attributes[position];
}

XMLElementNode& XMLElementNode::set_attribute_at(unsigned position, const Attribute& attribute)
{
	element_attributes[position] = attribute;
	return *this;
}

XMLElementNode::XMLElementNode(const Attribute& id, const Tag& tag, const std::vector<Attribute>& attributes, std::vector<XMLRootNode*> children)
{
	//TODO - евнтуално някакви чекове

	unique_id = id;
	element_attributes = attributes;
	element_tag = tag;
	element_children = children;
}
