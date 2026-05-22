#include "XMLTextNode.h"
#include <iostream>
#include "XMLTextContent.h"


XMLTextNode::XMLTextNode()
{
}

XMLTextNode::XMLTextNode(const std::string& text_content):content(text_content)
{
	
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
