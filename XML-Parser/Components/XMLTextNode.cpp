#include "XMLTextNode.h"
#include <iostream>
#include "XMLTextContent.h"


XMLTextNode::XMLTextNode()
{
}

XMLTextNode::XMLTextNode(const std::string& text_content):content(text_content)
{
	
}

std::vector<XMLNode*> XMLTextNode::get_root_children_with_tag(const std::string& user_command)
{
	return std::vector<XMLNode*>();
}

void  XMLTextNode::print(std::ostream& out, unsigned depth) const
{
	out << std::string(depth * 4, ' ') << content.get_content() <<"\n";

}

const std::string XMLTextNode::get_type() const
{
	return "TextNode";
}

void XMLTextNode::generate_unique_ids(UniqueId& values)
{
	return;
}

const XMLTextContent& XMLTextNode::get_text_node() const
{
	return content;
}

const std::string XMLTextNode::get_string() const 
{
	return content.get_content();
}

XMLTextNode& XMLTextNode::set_text_node(const std::string& text_content)
{
	content = XMLTextContent(text_content);
	return *this;
}

XMLNode* XMLTextNode::copy()
{
	return new XMLTextNode(this->content.get_content());
}

std::vector<Attribute> XMLTextNode::get_attributes()
{
	return std::vector<Attribute>();
}

Attribute XMLTextNode::get_id()
{
	return Attribute();
}

void XMLTextNode::set_id(Attribute& id, const std::string& value)
{
	return;
}

std::string XMLTextNode::get_text_content()
{
	return this->content.get_content();
}

std::vector<XMLNode*> XMLTextNode::get_children()
{
	return std::vector<XMLNode*>(); // Текстът няма деца
}

std::string XMLTextNode::get_tag_name()
{
	return ""; // Текстът няма таг
}