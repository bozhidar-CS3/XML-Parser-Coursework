#include "UserInterface.h"

void UserInterface::start_program()
{
	std::string command;
	while (true)
	{

		std::getline(std::cin, command);
		get_next_user_command(command);

	}

}

void UserInterface::get_next_user_command(const std::string& next)
{
	user_command = next;
}

void UserInterface::parse_user_command(const std::string& command)
{
	if (command == "Save")
	{
		save();
	}
	if (command == "Exit")
	{
		acepting_comands = false;
		std::cout << "Sucesfully exited!\n";
	}
	if (command == "Print")
	{
		if (is_file_open == true)
		{
			std::cout << "Starting print: \n";
			tree->print(std::cout, 8);
			return;
		}
		else
		{
			std::cout << "File is not opened!\n";
			return;
		}
	}
	if (command == "Help")
	{
		help();
	}
	size_t pos_of_space = command.find(' ');
	if (pos_of_space != std::string::npos)
	{
		std::string actual_command = command.substr(0, pos_of_space);
		if (actual_command == "Open")
		{
			open_file(command);
		}
		else if (actual_command == "Saveas")
		{
			save_as(command);
		}
		else if(actual_command == "Select")
		{
			select(command);
		}
	}
}

void UserInterface::save()
{
		std::ofstream file(filepath);
		if (!file.is_open())
		{
			std::cout << "Start file is gone!";
		}
		else
		{
			tree->print(file, 8);
		}
	
}

void UserInterface::open_file(const std::string& command)
{
	size_t start_of_filepath = command.find('\"');
	size_t end_of_filepath = command.rfind('\"');
	std::string filepath = command.substr(start_of_filepath, end_of_filepath - start_of_filepath + 1);
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		std::cout << "Eror opening the file!Creating a new, empty one! \n";
		std::ofstream new_file(filepath);
		if (new_file.is_open())
		{
			std::cout << "Created new file! \n";
			new_file.close();
		}
		else
		{
			std::cout << "Erorr with the path! \n";
		}
	}
	std::cout << "File opened !\n";
	tree = parse(file);
	if (tree == nullptr)
	{
		std::cout << "XML error!\n";
	}
	else
	{
		std::cout << "Tree sucesesfully parsed!\n";
		is_file_open = true;
	}
}

void UserInterface::help()
{
	std::ifstream file("C:\\Users\\dwd6\\Desktop\\Fmi - UpPraktikum\\XML - Parser\\XML - Parser\\x64\\Debug\\help.txt.txt");
	if (file.is_open())
	{
		std::string line;
		while(std::getline(file,line))
		{
			std::cout << line;
		}
	}
	else
	{
		std::cout << "No help file \n";
	}
}

void UserInterface::save_as(const std::string& command)
{
	if (is_file_open == false)
	{
		std::cout << "Cant't save a file because none are open! \n";
		return;
	}

	size_t start_of_file_path = command.find('\"');
	size_t end_of_file_path = command.rfind('\"');
	std::string file_name = command.substr(start_of_file_path, end_of_file_path - start_of_file_path);
//	size_t space = junk.find(' ');
//	std::string file_name = junk.substr(space, end_of_file_path -space - 1);
	//std::string file_path = junk.substr(0, space);
	std::ofstream file(file_name);
	if (!file.is_open())
	{
		std::cout << "Cant, create file!\n";
		return;
	}
	else
	{
		tree->print(file, 8);
		return;
	}
	file.close();
}

void UserInterface::select(const std::string& command)
{
	size_t pos_of_space = command.find(' ');
	if (pos_of_space == std::string::npos)
	{
		std::cout << "Invalid command!\n";
		return;
	}
	size_t second_space = command.find(' ', pos_of_space);
	if (second_space == std::string::npos)
	{
		std::cout << "Invalid command!\n";
		return;
	}
	std::string id_value = command.substr(pos_of_space, second_space - pos_of_space);
	std::string key = command.substr(second_space + 1);
	std::cout<<"Attribute value is: "<< engine.find_attribute_value(tree, id_value, key)<<"\n";
	return;
}

XMLNode* UserInterface::parse(std::ifstream& file, const Tag& expected_tag)
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
