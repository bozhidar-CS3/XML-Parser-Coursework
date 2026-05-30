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
#include "Commands/XMLXpath.h"



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
		std::string clean_text = command.trim(token);
		if (!clean_text.empty())
		{
			return new XMLTextNode(clean_text);
		}
		else
		{
			return nullptr;
		}
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
		//Добавяме още една проверка за граничен случай самозатварящ се таг

		if (token.length() >= 2 && token[token.length() - 2] == '/')
		{
			return curent_element;
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


#include <windows.h> //за кирилица на windows
int main()
{
	//SetConsoleOutputCP(CP_UTF8); //за кирилица на windows
	//std::ifstream file("C:\\Users\\dwd6\\Desktop\\Fmi-UpPraktikum\\XML-Parser\\XML-Parser\\x64\\Debug\\test.xml.txt");
	//if (!file.is_open())
	//{
	//	std::cerr << "Critical Error: file test.xml cannot be opened!\n";
	//	return 1; // Спираме програмата
	//}

	//XMLNode* root = nullptr;

	//// 2. Защитената зона (Опитваме да парснем)
	//try
	//{
	//	std::cout << "Start reading file \n";

	//	// Викаме нашата рекурсивна функция (подаваме файла)
	//	root = parse(file);

	//	if (root != nullptr)
	//	{
	//		std::cout << "\n=== Succes! ===\n";
	//		std::cout << "XML tree is build!\n";

	//		// Ако имаш написана функция за принтиране (напр. root->print()), 
	//		// тук е моментът да я извикаш, за да видиш резултата на екрана.
	//	}
	//	else
	//	{
	//		std::cout << "File is empty or has no root.\n";
	//	}
	//}
	//// 3. Спасителният екип (Хващаме синтактични грешки)
	//catch (const std::exception& e)
	//{
	//	std::cerr << "\n=== Error Parsing ===\n";
	//	std::cerr << e.what() << "\n";
	//	std::cerr << "Tree is broken.\n";
	//}

	//// 4. Почистване на паметта (МНОГО ВАЖНО!)
	//// Дори програмата да е гръмнала по средата, ако root не е nullptr,
	//// това извикване ще задейства деструкторите рекурсивно и ще изтрие всичко!
	//delete root;

	//// Затваряме файла културно
	//file.close();
	// 
	// 

	std::ifstream file("C:\\Users\\dwd6\\Desktop\\Fmi-UpPraktikum\\XML-Parser\\XML-Parser\\x64\\Debug\\test.xml.txt");

	if (!file.is_open())
	{
		std::cout << "DEBUG ERROR: File could not be opened!\n";
		return 1;
	}

	XMLNode* root = parse(file);

	if (root == nullptr)
	{
		std::cout << "DEBUG ERROR: Root is nullptr!\n";
		return 1;
	}

	UniqueId global_id_generator;
	Xpath xpath_engine;

	// Ако нямаш функция assign_unique_ids, закоментирай този ред
	// xpath_engine.assign_unique_ids(root, global_id_generator);

	std::cout << "\n========== DEBUG START ==========\n";

	// 1. Проверяваме децата на root
	std::vector<XMLNode*> root_children = root->get_children();
	std::cout << "STEP 1: Root has " << root_children.size() << " children.\n";

	for (size_t i = 0; i < root_children.size(); ++i)
	{
		XMLNode* child = root_children[i];
		std::cout << "  Child " << i << " | Type: [" << child->get_type() << "]";
		if (child->get_type() == "ElementNode")
		{
			std::cout << " | Tag: [" << child->get_tag_name() << "]\n";
		}
		else
		{
			std::cout << "\n";
		}
	}

	std::cout << "\nSTEP 2: Testing root->get_root_children_with_tag(\"garage\")\n";
	std::vector<XMLNode*> step1_garages = root->get_root_children_with_tag("garage");
	std::cout << "  Found garages: " << step1_garages.size() << "\n";

	// Ако функцията ти не го намери, търсим го ръчно, за да не спре тестът!
	if (step1_garages.empty())
	{
		std::cout << "  DEBUG: get_root_children_with_tag failed! Trying manual search...\n";
		for (XMLNode* child : root_children)
		{
			if (child->get_type() == "ElementNode" && child->get_tag_name() == "garage")
			{
				step1_garages.push_back(child);
				std::cout << "  DEBUG: Garage found manually!\n";
			}
		}
	}

	std::cout << "\nSTEP 3: Searching for 'vehicle' inside found garages\n";
	std::vector<XMLNode*> step2_vehicles;
	for (XMLNode* garage : step1_garages)
	{
		std::vector<XMLNode*> garage_children = garage->get_children();
		std::cout << "  Current garage has " << garage_children.size() << " children.\n";

		for (XMLNode* child : garage_children)
		{
			if (child->get_type() == "ElementNode")
			{
				std::cout << "    Found element in garage: [" << child->get_tag_name() << "]\n";
				if (child->get_tag_name() == "vehicle")
				{
					step2_vehicles.push_back(child);
				}
			}
		}
	}
	std::cout << "  Total cars found: " << step2_vehicles.size() << "\n";


	std::cout << "\nSTEP 4: Testing person filter\n";
	std::vector<XMLNode*> all_persons;
	for (XMLNode* garage : step1_garages)
	{
		for (XMLNode* child : garage->get_children())
		{
			if (child->get_type() == "ElementNode" && child->get_tag_name() == "person")
			{
				all_persons.push_back(child);
			}
		}
	}
	std::cout << "  Total persons found before filter: " << all_persons.size() << "\n";

	// Забележка: В XML-а address е атрибут, затова тук тестваме детето-таг <name> с текст Ivan!
	std::vector<XMLNode*> bg_persons = xpath_engine.get_element_where_x_is_true(all_persons, "name", "Ivan");
	std::cout << "  Total persons named Ivan found: " << bg_persons.size() << "\n";

	std::cout << "========== DEBUG END ==========\n";

	return 0;

	//NEW
	// 
	
	//if (!file.is_open())
	//{
	//	std::cout << "Can't open the file!\n";
	//	return 1;
	//}

	//XMLNode* root = parse(file);
	//if (root == nullptr)
	//{
	//	std::cout << "Can't start (parsing failed)!\n";
	//	return 1;
	//}

	//std::cout << "====== Tree is built ======\n\n";

	//// Създаваме обект от твоя клас (ако функциите не са static)
	//Xpath xpath_engine;

	//// ==========================================
	//// ТЕСТ 1: Филтър по стойност -> person[address="Bulgaria"]
	//// ==========================================
	//std::cout << "--- TEST 1: person[address=\"Bulgaria\"] ---\n";

	//// Стъпка 1: Намираме всички хора
	//std::vector<XMLNode*> all_persons = root->get_root_children_with_tag("garage/person");
	//// Стъпка 2: Удряме филтъра! (Очакваме да върне само Иван и Георги)
	//std::vector<XMLNode*> bg_residents = xpath_engine.get_element_where_x_is_true(all_persons, "address", "Bulgaria");

	//if (bg_residents.empty()) {
	//	std::cout << "No people found from Bulgaria!\n";
	//}
	//else {
	//	std::cout << "Found " << bg_residents.size() << " people from Bulgaria:\n";
	//	for (XMLNode* p : bg_residents)
	//	{
	//		p->print(std::cout, 0);
	//		std::cout << "\n-------------------\n";
	//	}
	//}


	//// ==========================================
	//// ТЕСТ 2: Търсене на атрибути -> vehicle[@id]
	//// ==========================================
	//std::cout << "\n--- TEST 2: vehicle[@id] ---\n";

	//// Стъпка 1: Намираме всички коли
	//std::vector<XMLNode*> all_vehicles = root->get_root_children_with_tag("garage/vehicle");

	//// Стъпка 2: Вадим само атрибутите "id" (Нисанът трябва да бъде пропуснат!)
	//std::vector<Attribute> ids = xpath_engine.get_all_attributes_with_name("id", all_vehicles);

	//if (ids.empty()) {
	//	std::cout << "No IDs found!\n";
	//}
	//else {
	//	std::cout << "Found " << ids.size() << " IDs:\n";
	//	for (const Attribute& attr : ids)
	//	{
	//		std::cout << attr.get_attribute_name() << " = " << attr.get_attribute_value() << "\n";
	//	}
	//}

	//delete root;
	//if (!file.is_open())
	//{
	//	std::cout << "Can't open the file!\n";
	//	return 1;
	//}

	//// 2. Парсваме го (извикай твоята функция за парсване)
	//XMLNode* root = parse(file);
	//if (root == nullptr)
	//{
	//	std::cout << "can't start!\n";
	//	return 1;
	//}

	//std::cout << "====== tree is built ======\n\n";

	//// ==========================================
	//// ТЕСТОВЕ НА XPATH С ТВОЯ ФАЙЛ
	//// ==========================================

	//// --- ТЕСТ 1: Търсим всички коли ---
	//std::cout << "--- TEST 1: garage/vehicle ---\n";
	//std::vector<XMLNode*> vehicles = root->get_root_children_with_tag("garage/vehicle");

	//if (vehicles.empty()) {
	//	std::cout << "NO cars!\n";
	//}
	//else {
	//	std::cout << "found " << vehicles.size() << " cars:\n";
	//	for (XMLNode* v : vehicles)
	//	{
	//		v->print(std::cout,0); // Принтираме ги
	//		std::cout << "-------------------\n";
	//	}
	//}

	//// --- ТЕСТ 2: Търсим собствениците на коли ---
	//std::cout << "\n--- TEST 2: garage/vehicle/owner ---\n";
	//std::vector<XMLNode*> owners = root->get_root_children_with_tag("garage/vehicle/owner");

	//if (owners.empty()) {
	//	std::cout << "no owners!\n";
	//}
	//else {
	//	std::cout << "found: " << owners.size() << " owners:\n";
	//	for (XMLNode* o : owners)
	//	{
	//		o->print(std::cout, 0);
	//		std::cout << "\n-------------------\n";
	//	}
	//}

	//// --- ТЕСТ 3: Търсим историята и годината ---
	//std::cout << "\n--- TEST 3: garage/history/year ---\n";
	//std::vector<XMLNode*> years = root->get_root_children_with_tag("garage/history/year");

	//if (years.empty()) {
	//	std::cout << "year not found!\n";
	//}
	//else {
	//	std::cout << "found year:\n";
	//	for (XMLNode* y : years)
	//	{
	//		y->print(std::cout, 0);
	//		std::cout << "\n-------------------\n";
	//	}
	//}

	//// --- ТЕСТ 4: Търсим самозатварящия се таг ---
	//std::cout << "\n--- TEST 4: garage/self_closing_tag ---\n";
	//std::vector<XMLNode*> self_closing = root->get_root_children_with_tag("garage/self_closing_tag");

	//if (self_closing.empty()) {
	//	std::cout << "No tag!\n";
	//}
	//else {
	//	std::cout << "Found tag:\n";
	//	for (XMLNode* tag : self_closing)
	//	{
	//		tag->print(std::cout, 0);
	//		std::cout << "\n-------------------\n";
	//	}
	//}

	//// 3. Почистваме паметта (ако имаш деструктор/функция за триене)
	// delete root; 

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
