#include "XMLElementNode.h"
#include <string>
#include "../Commands/ReadXMLFile.h"

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

XMLElementNode::XMLElementNode( std::string& line)
{
	XMLCommands commands;
	commands.fill_attributes(line, element_attributes);
	commands.fill_tags(line, element_tag);
	
}


//TODO fix it
const std::string XMLElementNode::get_string() const
{
	return "Id " + unique_id.get_attribute_name() + " " + unique_id.get_attribute_value() + " " + element_tag.get_opening_tag();
}

const std::string XMLElementNode::get_type() const
{
	return "ElementNode";
}

size_t XMLElementNode::get_children_count() const
{
	return element_children.size();
}

void XMLElementNode::generate_unique_ids(UniqueId& values)
{
	values.create_unique_ids(element_attributes, unique_id);
	if (element_children.empty())
	{
		return;
	}
	for (XMLNode* i : element_children)
	{
		i->generate_unique_ids(values);
	}
}

void XMLElementNode::add_child(XMLNode* child)
{
	element_children.push_back(child);
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


size_t XMLElementNode::get_attributes_count() const
{
	return element_attributes.size();
}

//std::vector<XMLElementNode*> XMLElementNode::get_element_node_children()
//{
//	std::vector<XMLNode* > children_copy;
//	for (size_t i = 0; i < element_children.size(); ++i )
//	{
//		if (element_children[i]->get_type() == "ElementNode")
//		{
//			XMLElementNode cur()
//			children_copy.push_back(element_children[i]->copy());
//		}
//	}
//	return children_copy;
//}

void XMLElementNode::set_attributes(const std::vector<Attribute>& other)
{
	for (Attribute i:other)
	{
		this->element_attributes.push_back(i);
	}
}

XMLElementNode::XMLElementNode(const XMLElementNode& other)
{
	this->unique_id = other.unique_id;
	this->element_attributes = other.element_attributes;
	this->element_tag = other.element_tag;
	for (XMLNode* i:other.element_children)
	{
		this->element_children.push_back(i->copy());
	}
}

XMLNode* XMLElementNode::copy()
{
	return new XMLElementNode(*this);
}

const Attribute& XMLElementNode::get_attribute_at(unsigned position) const
{
	
	return element_attributes.at(position);
}

XMLElementNode& XMLElementNode::set_attribute_at(unsigned position, const Attribute& attribute)
{
	element_attributes[position] = attribute;
	return *this;
}

XMLElementNode::XMLElementNode(const Attribute& id, const Tag& tag, const std::vector<Attribute>& attributes, std::vector<XMLNode*> children)
{
	//TODO - евнтуално някакви чекове

	unique_id = id;
	element_attributes = attributes;
	element_tag = tag;
	element_children = children;
}
