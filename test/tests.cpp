#define CATCH_CONFIG_MAIN

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

    list.removeIndex(2);
    list.removeIndex(2);
    list.removeIndex(0);
    list.removeIndex(0);
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
