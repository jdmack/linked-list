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
}