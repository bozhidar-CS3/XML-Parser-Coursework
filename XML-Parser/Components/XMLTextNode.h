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

	std::vector<XMLNode*> get_root_children_with_tag(const std::string& user_command) override;
	void print(std::ostream& out, unsigned depth) const override;
	const std::string get_type() const override;
	void generate_unique_ids(UniqueId& values) override;
	const  XMLTextContent& get_text_node() const;
	const std::string get_string()  const override;
	XMLTextNode& set_text_node(const std::string& text_content);
	XMLNode* copy() override;

	std::vector<Attribute> get_attributes() override;
	Attribute get_id() override;
	void set_id(Attribute& id, const std::string& value) override;
	std::string get_text_content() override;

	std::vector<XMLNode*> get_children() override;
	std::string get_tag_name() override;

};
