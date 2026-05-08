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

    std::cout << "XMLTextNode test! \n";
    std::vector<XMLRootNode> arr;
    XMLTextNode content1("Pesho");
   
    std::cout << content1.get_text_node().get_content()<< " or " << content1.get_string()<<"\n";
    XMLTextNode node2;
    std::cout << node2.get_text_node().get_content() << " or " << node2.get_string() << "\n";

    XMLTextNode node3("Initial");

    node3.set_text_node("Middle").set_text_node("Final Text");

    std::cout << "Expected: Final Text \nActual:   "
        << node3.get_text_node().get_content() <<" or " << node3.get_string() << "\n\n";

    std::vector<XMLRootNode*> tree_nodes;
    tree_nodes.push_back(new XMLTextNode("John Doe"));
    tree_nodes.push_back(new XMLTextNode("New York"));

    for (size_t i = 0; i < tree_nodes.size(); i++)
    {
      std::cout <<   tree_nodes[i]->get_string();
    }

    for (size_t i = 0; i < tree_nodes.size(); i++)
    {
        delete tree_nodes[i];
    }
    tree_nodes.clear(); // чистим указателите във вектора.
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
