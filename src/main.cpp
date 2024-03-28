/*
Create a C++ program that implements a linked list. The linked list should be
a doubly linked list, allowing movement forward and backward. This program
should allow you to add and remove nodes from the list. Each node should
contain a reference to application data. The program does not have to provide
user interaction. Please include units tests for the program.

[X] LinkedList header
[X] insert()
[X] remove()
[X] lookup()
[X] []
[X] tests
[ ] 
[ ] templates
[ ] node recycling
[ ] comments




*/

#include <iostream>
#include "LinkedList.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World" << std::endl;

    LinkedList list;
    list.insert(0);
    // list.insert(1);
    // list.insert(2);
    // list.insert(3);

    std::cout << list.toStr() << std::endl;

    list.remove(0);

    std::cout << list.toStr() << std::endl;

    return 0;
}