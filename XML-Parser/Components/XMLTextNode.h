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

	void print(std::ostream& out, unsigned depth) const override;
	const std::string get_type() const override;
	void generate_unique_ids(UniqueId& values) override;
	const  XMLTextContent& get_text_node() const;
	const std::string get_string()  const override;
	XMLTextNode& set_text_node(const std::string& text_content);
	XMLNode* copy() override;
};
