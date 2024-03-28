#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "../src/LinkedList.h"

TEST_CASE("Create list", "[create]")
{
    LinkedList list;

    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Inserting single element", "[insert]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");
}

TEST_CASE("Inserting multiple elements", "[insert]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Insert at index 0 in empty list", "[insert]")
{
    LinkedList list;

    REQUIRE_NOTHROW(list.insert(0, 0));
    REQUIRE(list.toStr() == "[0]");
}

TEST_CASE("Insert at out of bounds index in empty list", "[insert]")
{
    LinkedList list;

    REQUIRE_THROWS_AS(list.insert(0, 1), std::out_of_range);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Insert at negative index in empty list", "[insert]")
{
    LinkedList list;

    REQUIRE_THROWS_AS(list.insert(0, -1), std::out_of_range);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Insert at index=occupancy ", "[insert]")
{
    LinkedList list;

    REQUIRE_NOTHROW(list.insert(0, 0));
    REQUIRE_NOTHROW(list.insert(1, 1));
    REQUIRE_NOTHROW(list.insert(2, 2));
    REQUIRE(list.toStr() == "[0 1 2]");

    REQUIRE_NOTHROW(list.insert(3, 3));
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Insert multiple at index", "[insert]")
{
    LinkedList list;

    REQUIRE_NOTHROW(list.insert(0, 0));
    REQUIRE(list.toStr() == "[0]");
    
    std::cout << list.toStrDetails();

    // Insert at head with occupancy=1
    REQUIRE_NOTHROW(list.insert(1, 0));
    REQUIRE(list.toStr() == "[1 0]");

    // Insert at tail with occupancy=1
    REQUIRE_NOTHROW(list.removeIndex(0));
    REQUIRE(list.toStr() == "[0]");

    REQUIRE_NOTHROW(list.insert(1, 1));
    REQUIRE(list.toStr() == "[0 1]");

    // Insert at head with occupancy=2
    REQUIRE(list.toStr() == "[0 1]");
    REQUIRE_NOTHROW(list.insert(2, 0));
    REQUIRE(list.toStr() == "[2 0 1]");

    // Insert at tail with occupancy=2
    REQUIRE_NOTHROW(list.removeIndex(0));
    REQUIRE(list.toStr() == "[0 1]");

    REQUIRE_NOTHROW(list.insert(2, 2));
    REQUIRE(list.toStr() == "[0 1 2]");

    // Insert before tail with occupancy=2
    REQUIRE_NOTHROW(list.removeIndex(2));
    REQUIRE(list.toStr() == "[0 1]");

    REQUIRE_NOTHROW(list.insert(2, 1));
    REQUIRE(list.toStr() == "[0 2 1]");
}

TEST_CASE("Insert at out of bounds index", "[insert]")
{
    LinkedList list;

    REQUIRE_NOTHROW(list.insert(0, 0));
    REQUIRE_NOTHROW(list.insert(1, 1));
    REQUIRE_NOTHROW(list.insert(2, 2));
    REQUIRE(list.toStr() == "[0 1 2]");

    REQUIRE_THROWS_AS(list.insert(3, 4), std::out_of_range);
}

TEST_CASE("Insert at negative index ", "[insert]")
{
    LinkedList list;

    REQUIRE_NOTHROW(list.insert(0, 0));
    REQUIRE_NOTHROW(list.insert(1, 1));
    REQUIRE_NOTHROW(list.insert(2, 2));
    REQUIRE(list.toStr() == "[0 1 2]");

    REQUIRE_THROWS_AS(list.insert(3, -1), std::out_of_range);
}

TEST_CASE("Remove element from empty list", "[remove]")
{
    LinkedList list;

    list.remove(0);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Remove element from list with occupancy=1", "[remove]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    list.remove(0);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Remove head from list", "[remove]")
{
    LinkedList list;

    // Remove head from list with occupancy=2
    list.insert(0);
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    list.remove(0);
    REQUIRE(list.toStr() == "[1]");

    // Remove head with occupancy=3
    list.insert(0);
    list.insert(2);
    REQUIRE(list.toStr() == "[1 0 2]");

    list.remove(1);
    REQUIRE(list.toStr() == "[0 2]");
}

TEST_CASE("Remove tail from list", "[remove]")
{
    LinkedList list;

    // Remove tail from list with occupancy=2
    list.insert(0);
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    list.remove(1);
    REQUIRE(list.toStr() == "[0]");

    // Remove tail with occupancy=3
    list.insert(1);
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    list.remove(2);
    REQUIRE(list.toStr() == "[0 1]");
}

TEST_CASE("Removing multiple elements", "[remove]")
{
    LinkedList list;

    for (int i = 0; i < 10 ; ++i) {
        list.insert(i);
    }
    REQUIRE(list.toStr() == "[0 1 2 3 4 5 6 7 8 9]");

    for (int i = 0; i < 10 ; ++i) {
        list.remove(i);
    }
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Multiple insertions and removals", "[other]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    list.remove(1);
    list.insert(3);
    list.insert(4);
    list.remove(0);
    list.insert(5);
    list.insert(6);
    list.remove(5);
    list.insert(7);
    list.remove(7);
    REQUIRE(list.toStr() == "[2 3 4 6]");

    list.insert(8);
    list.insert(9);
    REQUIRE(list.toStr() == "[2 3 4 6 8 9]");

    list.remove(2);
    list.remove(3);
    list.remove(9);
    list.remove(4);
    list.remove(6);
    list.remove(8);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Remove element by index", "[remove]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    REQUIRE_NOTHROW(list.removeIndex(2));
    REQUIRE_NOTHROW(list.removeIndex(2));
    REQUIRE_NOTHROW(list.removeIndex(0));
    REQUIRE_NOTHROW(list.removeIndex(0));
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Remove element by index - out of range", "[remove]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    REQUIRE_THROWS_AS(list.removeIndex(4), std::out_of_range);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Remove element by index - negative index", "[remove]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    REQUIRE_THROWS_AS(list.removeIndex(-1), std::out_of_range);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Element access via function - empty list", "[access]")
{
    LinkedList list;

    REQUIRE(list.toStr() == "[]");

    REQUIRE_THROWS_AS(list.at(0), std::out_of_range);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Element access via function - index out of range", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    REQUIRE_THROWS_AS(list.at(4), std::out_of_range);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Element access via function - index negative", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    REQUIRE_THROWS_AS(list.at(-1), std::out_of_range);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Element access via operator - empty list", "[access]")
{
    LinkedList list;

    REQUIRE(list.toStr() == "[]");

    int value = 1337;

    REQUIRE_THROWS_AS(value = list[0], std::out_of_range);
    REQUIRE(value == 1337);
    REQUIRE(list.toStr() == "[]");
}

TEST_CASE("Element access via operator - index out of range", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    int value = 1337;

    REQUIRE_THROWS_AS(value = list[4], std::out_of_range);
    REQUIRE(value == 1337);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Element access via operator - index negative", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    REQUIRE(list.toStr() == "[0 1 2 3]");

    int value = 1337;

    REQUIRE_THROWS_AS(value = list[-1], std::out_of_range);
    REQUIRE(value == 1337);
    REQUIRE(list.toStr() == "[0 1 2 3]");
}

TEST_CASE("Element access via function - occupancy=1", "[access]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    int value = 1337;

    REQUIRE_NOTHROW(value = list.at(0));
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0]");
}

TEST_CASE("Element access via function - occupancy=2", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    int value = 1337;

    // Access head element
    REQUIRE_NOTHROW(value = list.at(0));
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0 1]");

    // Access tail element
    REQUIRE_NOTHROW(value = list.at(1));
    REQUIRE(value == 1);
    REQUIRE(list.toStr() == "[0 1]");
}

TEST_CASE("Element access via function - occupancy=3", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    int value = 1337;

    // Access head element
    REQUIRE_NOTHROW(value = list.at(0));
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Access middle element
    REQUIRE_NOTHROW(value = list.at(1));
    REQUIRE(value == 1);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Access tail element
    REQUIRE_NOTHROW(value = list.at(2));
    REQUIRE(value == 2);
    REQUIRE(list.toStr() == "[0 1 2]");
}

TEST_CASE("Element access via operator - occupancy=1", "[access]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    int value = 1337;

    REQUIRE_NOTHROW(value = list[0]);
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0]");
}

TEST_CASE("Element access via operator - occupancy=2", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    int value = 1337;

    // Access head element
    REQUIRE_NOTHROW(value = list[0]);
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0 1]");

    // Access tail element
    REQUIRE_NOTHROW(value = list[1]);
    REQUIRE(value == 1);
    REQUIRE(list.toStr() == "[0 1]");
}

TEST_CASE("Element access via operator - occupancy=3", "[access]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    int value = 1337;

    // Access head element
    REQUIRE_NOTHROW(value = list[0]);
    REQUIRE(value == 0);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Access middle element
    REQUIRE_NOTHROW(value = list[1]);
    REQUIRE(value == 1);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Access tail element
    REQUIRE_NOTHROW(value = list[2]);
    REQUIRE(value == 2);
    REQUIRE(list.toStr() == "[0 1 2]");
}

TEST_CASE("Lookup empty list", "[lookup]")
{
    LinkedList list;

    REQUIRE(list.lookup(0) == -1);
}

TEST_CASE("Lookup success with occupancy=1", "[lookup]")
{
    LinkedList list;

    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    REQUIRE(list.lookup(0) == 0);
    REQUIRE(list.toStr() == "[0]");
}

TEST_CASE("Lookup success with occupancy=2", "[lookup]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    // Lookup head
    REQUIRE(list.lookup(0) == 0);
    REQUIRE(list.toStr() == "[0 1]");

    // Lookup tail
    REQUIRE(list.lookup(1) == 1);
    REQUIRE(list.toStr() == "[0 1]");
}

TEST_CASE("Lookup success with occupancy=3", "[lookup]")
{
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Lookup head
    REQUIRE(list.lookup(0) == 0);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Lookup middle
    REQUIRE(list.lookup(1) == 1);
    REQUIRE(list.toStr() == "[0 1 2]");

    // Lookup tail
    REQUIRE(list.lookup(2) == 2);
    REQUIRE(list.toStr() == "[0 1 2]");
}

TEST_CASE("Lookup not found", "[lookup]")
{
    LinkedList list;

    // Lookup failure with occupany=1
    list.insert(0);
    REQUIRE(list.toStr() == "[0]");

    REQUIRE(list.lookup(-1) == -1);
    REQUIRE(list.toStr() == "[0]");

    // Lookup failure with occupany=2
    list.insert(1);
    REQUIRE(list.toStr() == "[0 1]");

    REQUIRE(list.lookup(-1) == -1);
    REQUIRE(list.toStr() == "[0 1]");

    // Lookup failure with occupany=3
    list.insert(2);
    REQUIRE(list.toStr() == "[0 1 2]");

    REQUIRE(list.lookup(-1) == -1);
    REQUIRE(list.toStr() == "[0 1 2]");
}

TEST_CASE("Size", "[size]")
{
    LinkedList list;

    // Size of empty list
    REQUIRE(list.size() == 0);
    REQUIRE(list.toStr() == "[]");

    // Size of list with occupancy=1
    list.insert(0);
    REQUIRE(list.size() == 1);
    REQUIRE(list.toStr() == "[0]");

    // Size of list with occupancy=2
    list.insert(1);
    REQUIRE(list.size() == 2);
    REQUIRE(list.toStr() == "[0 1]");

    // Size of list with occupancy=3
    list.insert(2);
    REQUIRE(list.size() == 3);
    REQUIRE(list.toStr() == "[0 1 2]");
}

















