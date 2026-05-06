// XML-Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tag.h"
#include "Attribute.h"
#include "XMLTextNode.h"
#include <string>

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
    
    XMLTextNode node1;
    std::cout << node1.get_XMLTextNode();
    node1.set_XMLTextNode("az");
    std::cout << node1.get_XMLTextNode();
    XMLTextNode node2("neshto");
    std::cout << node2.get_XMLTextNode();

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
