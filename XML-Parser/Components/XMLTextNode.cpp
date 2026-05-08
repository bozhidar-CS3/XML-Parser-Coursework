#include "XMLTextNode.h"
#include <iostream>
#include "XMLTextContent.h"


XMLTextNode::XMLTextNode()
{
}

XMLTextNode::XMLTextNode(const std::string& text_content):content(text_content)
{
	
}

const XMLTextContent& XMLTextNode::get_text_node() const
{
	return content;
}

const std::string& XMLTextNode::get_string() const 
{
	return content.get_content();
}

XMLTextNode& XMLTextNode::set_text_node(const std::string& text_content)
{
	content = XMLTextContent(text_content);
	return *this;
}
