#include <iostream>
#include <list>
#include "LinkedList.h"

int main(int argc, char ** argv)
{
    // std::cout << "Hello World" << std::endl;
    LinkedList<int> list;
    list.insert(0, 0);
    list.insert(1, 1);
    // list.insert(2);
    // list.insert(3);

    std::cout << list.toStr() << std::endl;
    std::cout << list.toStrDetails() << std::endl;

    // list.insert(2, 1);

    // list.remove(0);

    std::cout << list.toStr() << std::endl;
    std::cout << list.toStrDetails() << std::endl;

    return 0;
}