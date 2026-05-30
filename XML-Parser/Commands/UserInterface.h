#pragma once
#include <string>
#include "../Components/XMLNode.h"
#include "../Components/Tag.h"
#include "ReadXMLFile.h"
#include <fstream>
#include "../Commands//XMLXpath.h"



class UserInterface
{
public:
	void start_program();
	void get_next_user_command(const std::string& next);
	void parse_user_command(const std::string& command);
	void save();
	void open_file(const std::string& command);
	void help();
	void save_as(const std::string& command);
	void select(const std::string& command);
	XMLNode* parse(std::ifstream& file, const Tag& expected_tag = Tag());
private:
	Xpath engine;
	std::string user_command;
	std::string filepath ="";
	bool is_file_open;
	XMLNode* tree;
	bool acepting_comands;
};