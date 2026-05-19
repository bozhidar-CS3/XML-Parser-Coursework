#pragma once
#include "XMLNode.h"
#include "XMLTextContent.h"
#include <iostream>

class XMLTextNode :public XMLNode
{
	XMLTextContent content;
	
public:
	XMLTextNode();
	XMLTextNode(const std::string&);
	const  XMLTextContent& get_text_node() const;
	const std::string get_string()  const override;
	XMLTextNode& set_text_node(const std::string&);
	XMLNode* copy() override;
};
