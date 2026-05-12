#pragma once
#include "XMLRootNode.h"
#include "Tag.h"
#include "Attribute.h"
#include "XMLTextContent.h"
#include <vector>

class XMLElementNode : public XMLRootNode
{
	Attribute unique_id;

	Tag element_tag;

	std::vector<Attribute> element_attributes;

	std::vector<XMLRootNode*> element_children;

	//временен стринг за тестове
	std::string temp;
public:
	XMLElementNode();
	~XMLElementNode() override;

	const std::string get_string() const override;
	
	const Attribute& get_unique_id() const ;
	XMLElementNode& set_unique_id(const Attribute& );
	const Tag& get_element_tag() const;
	XMLElementNode& set_element_tag(const Tag&);
	
	const Attribute& get_attribute_at(unsigned position) const;
	XMLElementNode& set_attribute_at(unsigned position, const Attribute&);

	//Todo children

	XMLElementNode(const Attribute& id, const Tag& tag,const std::vector<Attribute>& attributes, std::vector<XMLRootNode*> children);

	//new

	void add_child(XMLRootNode* child) override;
};
