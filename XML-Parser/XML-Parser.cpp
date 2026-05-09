// XML-Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Components/Tag.h"
#include "Components/Attribute.h"
#include "Components/XMLTextContent.h"
#include "Components/XMLRootNode.h"
#include "Components/XMLTextNode.h"
#include <string>
#include <vector>
#include "Components/XMLElementNode.h"
#include "Commands/ReadXMLFile.h"
int main()
{
	//std::cout << "Test1\n";
	//Attribute test1;
	//std::cout << test1.get_attribute_name() << " " << test1.get_attribute_value() << " \n";

	//std::cout << "Test2\n";

	//Attribute test2("Dog", "2");
	//std::cout << test2.get_attribute_name() << " " << test2.get_attribute_value() << " \n";
	//std::cout << "Test3\n";

	//Attribute test3("Dog", "");
	//std::cout << test3.get_attribute_name() << " " << test3.get_attribute_value() << " \n";

	//XMLTextNode

  /*  XMLTextContent node1;
	std::cout << node1.get_content();
	node1.set_content("az");
	std::cout << node1.get_content();
	XMLTextContent node2("neshto");
	std::cout << node2.get_content();*/

	//std::cout << "XMLTextNode test! \n";
	//std::vector<XMLRootNode> arr;
	//XMLTextNode content1("Pesho");

	//std::cout << content1.get_text_node().get_content() << " or " << content1.get_string() << "\n";
	//XMLTextNode node2;
	//std::cout << node2.get_text_node().get_content() << " or " << node2.get_string() << "\n";

	//XMLTextNode node3("Initial");

	//node3.set_text_node("Middle").set_text_node("Final Text");

	//std::cout << "Expected: Final Text \nActual:   "
	//	<< node3.get_text_node().get_content() << " or " << node3.get_string() << "\n\n";

	//std::vector<XMLRootNode*> tree_nodes;
	//tree_nodes.push_back(new XMLTextNode("John Doe"));
	//tree_nodes.push_back(new XMLTextNode("New York"));

	//for (size_t i = 0; i < tree_nodes.size(); i++)
	//{
	//	std::cout << tree_nodes[i]->get_string();
	//}

	//for (size_t i = 0; i < tree_nodes.size(); i++)
	//{
	//	delete tree_nodes[i];
	//}
	//tree_nodes.clear(); // чистим указателите във вектора.

	// XMLElementNOde

	/*Tag person_tag;
	person_tag.set_tags("<Person>");
	Attribute person_id("Id", "e23");

	XMLElementNode rootElement;
	rootElement.set_element_tag(person_tag).set_unique_id(person_id);

	Tag nameTag;
	nameTag.set_tags("<name>");
	Attribute emptyId("", "");

	XMLElementNode* nameElement = new XMLElementNode();
	nameElement->set_element_tag(nameTag).set_unique_id(emptyId);

	XMLTextNode* nameText = new XMLTextNode("James Bond");

	std::cout << rootElement.get_string() << "\n";*/

	//функции тестове - генерирани от AI

	XMLCommands parser;
	std::cout << "=== TESTING STRING MANIPULATION ===\n\n";

	// ТЕСТ 1: Прости тагове и текст
	std::string line1 = "<name>";
	std::string line2 = "James Bond";

	std::cout << "Test 1: Is '<name>' a tag? " << (parser.check_for_tags(line1) ? "YES" : "NO") << " (Expected: YES)\n";


	std::cout << "Test 1: Is 'James Bond' a tag? " << (parser.check_for_tags(line2) ? "YES" : "NO") << " (Expected: NO)\n";
	std::cout << "Test 1: Is 'James Bond' text? " << (parser.check_for_text_content(line2) ? "YES" : "NO") << " (Expected: YES)\n\n";

	// ТЕСТ 2: Изваждане на име на таг
	Tag test_tag;
	std::string line3 = "<person id=\"007\">";
	parser.fill_tags(line3, test_tag);
	std::cout << "Test 2: Tag name extracted: " << test_tag.get_opening_tag() << " (Expected: <person>)\n\n";

	// ТЕСТ 3: Изваждане на сурови атрибути
	std::cout << "Test 3: Separating attributes from: " << line3 << "\n";
	std::string raw_attrs = parser.seperate_attributes_from_tag(line3);
	std::cout << "Result: [" << raw_attrs << "] (Expected: [id=\"007\"])\n\n";

	// ТЕСТ 4: Най-трудният тест - Множество атрибути със спейсове
	std::string complex_attributes = "id=\"1\" category=\"action movie\" lang=\"en\"";
	std::vector<Attribute> extracted_attributes;

	std::cout << "Test 4: Parsing multiple attributes...\n";
	parser.fill_attributes(complex_attributes, extracted_attributes);

	for (size_t i = 0; i < extracted_attributes.size(); i++)
	{
		std::cout << " - Attr " << i + 1 << ": Name=[" << extracted_attributes[i].get_attribute_name()
			<< "], Value=[" << extracted_attributes[i].get_attribute_value() << "]\n";
	}
	std::cout << "(Expected 3 attributes, value of 'category' should be 'action movie')\n\n";
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
