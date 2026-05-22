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



XMLNode* parse(std::ifstream& file, const Tag& expected_tag = Tag())
{
	XMLCommands command;
	std::string token = command.get_next_token(file);
	if (token.empty())
	{
		return nullptr;
	}

	if (command.check_for_text_node(token))
	{
		return new XMLTextNode(token);
	}

	if (command.check_for_lonely_end_tag(token))
	{
		Tag closing_tag;
		command.fill_tags(token, closing_tag);

		if (expected_tag.get_closing_tag() != "" && closing_tag.get_closing_tag() != expected_tag.get_closing_tag())
		{
			throw std::runtime_error("Wrong tag! Expected: " + expected_tag.get_closing_tag() + "Got: " + closing_tag.get_closing_tag());
		}
		return nullptr;
	}

	if (command.check_for_tags(token))
	{
		XMLElementNode* curent_element = new XMLElementNode();

		Tag el_tag;
		command.fill_tags(token, el_tag);
		curent_element->set_element_tag(el_tag);

		if (command.check_for_attributes(token))
		{
			std::vector<Attribute> attributes;
			command.fill_attributes(token, attributes);
			curent_element->set_attributes(attributes);
		}

		while (true)
		{
			XMLNode* child = parse(file, el_tag);
			if (child == nullptr)
			{
				break;
			}
			curent_element->add_child(child);
		}
		return curent_element;
	}
	throw std::runtime_error("Unknown XML format: " + token);
}
int main()
{
	
	std::ifstream file("C:\\Users\\dwd6\\Desktop\\Fmi-UpPraktikum\\XML-Parser\\XML-Parser\\x64\\Debug\\test.xml.txt");
	if (!file.is_open())
	{
		std::cerr << "Critical Error: file test.xml cannot be opened!\n";
		return 1; // Спираме програмата
	}

	XMLNode* root = nullptr;

	// 2. Защитената зона (Опитваме да парснем)
	try
	{
		std::cout << "Start reading file \n";

		// Викаме нашата рекурсивна функция (подаваме файла)
		root = parse(file);

		if (root != nullptr)
		{
			std::cout << "\n=== Succes! ===\n";
			std::cout << "XML tree is build!\n";

			// Ако имаш написана функция за принтиране (напр. root->print()), 
			// тук е моментът да я извикаш, за да видиш резултата на екрана.
		}
		else
		{
			std::cout << "File is empty or has no root.\n";
		}
	}
	// 3. Спасителният екип (Хващаме синтактични грешки)
	catch (const std::exception& e)
	{
		std::cerr << "\n=== Error Parsing ===\n";
		std::cerr << e.what() << "\n";
		std::cerr << "Tree is broken.\n";
	}

	// 4. Почистване на паметта (МНОГО ВАЖНО!)
	// Дори програмата да е гръмнала по средата, ако root не е nullptr,
	// това извикване ще задейства деструкторите рекурсивно и ще изтрие всичко!
	delete root;

	// Затваряме файла културно
	file.close();

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
