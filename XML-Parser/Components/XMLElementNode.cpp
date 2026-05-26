#include "XMLElementNode.h"
#include <string>
#include "../Commands/ReadXMLFile.h"
#include <exception>
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

XMLElementNode::XMLElementNode(std::string& line)
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

void XMLElementNode::print(std::ostream& out, unsigned depth) const
{
	std::string opening = element_tag.get_opening_tag();
	opening = opening.substr(0, opening.length() - 1);
	out << std::string(depth * 4, ' ') << opening;
	if (!unique_id.get_attribute_name().empty() && !unique_id.get_attribute_value().empty())
	{
		out << unique_id.get_attribute_name() << "=\"" << unique_id.get_attribute_value() << "\"";
	}

	if (!element_attributes.empty())
	{
		for (Attribute attribute : element_attributes)
		{
			out << ' ' << attribute.get_attribute_name() << "=\"" << attribute.get_attribute_value() << "\"";
		}
	}
	out << '>';

	if (!element_children.empty())
	{
		out << "\n";
		for (XMLNode* i : element_children)
		{
			i->print(out, depth + 1);
		}
		out << std::string(depth * 4, ' ') << element_tag.get_closing_tag() << "\n";
	}
	else
	{
		out << element_tag.get_closing_tag() << "\n";
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
	for (Attribute i : other)
	{
		this->element_attributes.push_back(i);
	}
}

XMLElementNode::XMLElementNode(const XMLElementNode& other)
{
	this->unique_id = other.unique_id;
	this->element_attributes = other.element_attributes;
	this->element_tag = other.element_tag;
	for (XMLNode* i : other.element_children)
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

std::vector<XMLNode*> XMLElementNode::get_root_children_with_tag(const std::string& user_command)
{
	if (user_command.empty())
	{
		return std::vector<XMLNode*>();
	}
	XMLCommands command;
	std::string root_tag, remainig_path;
	std::vector<XMLNode*> result_children;

	command.seperate_tags_from_user_command(user_command, root_tag, remainig_path);
	size_t opening_tag_lenght = element_tag.get_opening_tag().length();
	//element_tag.print_tag();

	//std::cout << root_tag << " " << remainig_path << "\n";
	std::string element_tag_without_brackets = element_tag.get_opening_tag().substr(1, opening_tag_lenght - 2);
	//std::cout << element_tag_without_brackets << "\n";
	if (element_tag_without_brackets != root_tag)
	{
	//	std::cout << "NOW root\n";
		return std::vector<XMLNode*>();

	}

	if (remainig_path.empty())
	{
	//	std::cout << "NOW no children\n ";
		result_children.push_back(this);
		return result_children;
	}

	//std::cout << "YEs children \n";
	for (XMLNode* i : element_children)
	{
		std::vector<XMLNode*> tmp = i->get_root_children_with_tag(remainig_path);
		for (XMLNode* j : tmp)
		{
	//		j->print(std::cout, 0);
			result_children.push_back(j);
		}
	}
	return result_children;
}

std::vector<Attribute> XMLElementNode::get_attributes()
{
	std::vector < Attribute> result;
	for (Attribute i: element_attributes )
	{
		result.push_back(i);
	}
	return result;
}

void XMLElementNode::set_id(Attribute& id, const std::string& name)
{
	id.set_attribute_value(name);
}

Attribute XMLElementNode::get_id()
{
	return unique_id;
}

std::string XMLElementNode::get_text_content()
{
	return "";
}

