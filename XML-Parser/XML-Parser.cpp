// XML-Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Components/Tag.h"
#include "Components/Attribute.h"
#include "Components/XMLTextContent.h"
#include "Components/XMLNode.h"
#include "Components/XMLTextNode.h"
#include <string>
#include <vector>
#include "Components/XMLElementNode.h"
#include "Commands/ReadXMLFile.h"




XMLNode* parse(std::string& line) 
{
	
	if (line.empty())
	{
		return nullptr;
	}

	XMLCommands command;
	if (command.check_for_text_node(line))
	{
		return new XMLTextNode(line);
	}
	Tag temp;
	Tag tmp;
	command.fill_tags(line, tmp);
	if (!command.check_for_lonely_end_tag(line) && command.check_for_end_tag(, line))
	{
		return nullptr;
	}
	
	// да седи този, за който още не сме намерили.


	


	if (command.check_for_tags(line))
	{

		XMLElementNode* cur_el = new XMLElementNode;
		Tag tag1;
		command.fill_tags(line, tag1);
		cur_el->set_element_tag(tag1);
		if (command.check_for_attribute(line))
		{
			std::vector<Attribute> h;
			command.fill_attributes(line, h);
			cur_el->set_attributes(h);
		}
		while (true)
		{
			XMLNode* child = parse(line);
			if (child == nullptr)
			{
				break;
			}
			cur_el->add_child(child);
		}
		return cur_el;
	}
	return nullptr;
}

int main()
{


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
