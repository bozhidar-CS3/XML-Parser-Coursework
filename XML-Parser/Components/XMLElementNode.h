#pragma once
#include "XMLNode.h"
#include "Tag.h"
#include "Attribute.h"
#include "XMLTextContent.h"
#include <vector>


class XMLElementNode : public XMLNode
{

	Attribute unique_id;

	Tag element_tag;

	std::vector<Attribute> element_attributes;

	std::vector<XMLNode*> element_children;



	//временен стринг за тестове
	std::string temp;
public:
	XMLElementNode();
	~XMLElementNode() override;
	XMLElementNode(std::string& line);
	const std::string get_string() const override;

	const std::string get_type() const override;

	size_t get_children_count() const;

	void generate_unique_ids(UniqueId& values) override;

	void print(std::ostream& out, unsigned depth) const override;

	void add_child(XMLNode* child);
	const Attribute& get_unique_id() const ;
	XMLElementNode& set_unique_id(const Attribute& );
	const Tag& get_element_tag() const;
	XMLElementNode& set_element_tag(const Tag&);
	
	size_t get_attributes_count() const;
//	std::vector<XMLElementNode*> get_element_node_children();

	void set_attributes(const std::vector<Attribute>& other);

	XMLElementNode(const XMLElementNode& other);
	XMLNode* copy() override;
	const Attribute& get_attribute_at(unsigned position) const;
	XMLElementNode& set_attribute_at(unsigned position, const Attribute&);

	//Todo children

	XMLElementNode(const Attribute& id, const Tag& tag,const std::vector<Attribute>& attributes, std::vector<XMLNode*> children);



	std::vector<XMLNode*> get_root_children_with_tag(const std::string& user_command) override;
	
	std::vector<Attribute> get_attributes() override;
	void set_id(Attribute& id, const std::string& name) override;
	Attribute get_id() override;
	std::string get_text_content() override;

	std::vector<XMLNode*> get_children() override;
	std::string get_tag_name();

	std::string get_unique_id_value() const override;

	void set_attribute_value(const std::string& value, const std::string& key) override;
	bool delete_attribute_by_key(const std::string& key)  override;

	bool newchild(XMLNode* child) override;
	//new

	//Рекурсия.
	//void add_child(XMLNode* child) override;

	//Трябва да си сменя името на базовия клас. Трябва да направя фактори.


};