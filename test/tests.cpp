#define CONFIG_CATCH_MAIN

#include "catch.hpp"
#include "../src/LinkedList.h"


TEST_CASE("Inserting multiple elements", "[insert]") {
    LinkedList list;

    list.insert(0);
    list.insert(1);
    list.insert(2);
    list.insert(3);

    REQUIRE(list.toStr() == "[0 1 2 3]");
}