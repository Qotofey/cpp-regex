#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include "../../include/textcalc.hpp"

TEST_CASE("test_function_do") {
    std::string tests[6];
    tests[0] = "12.00 / 24";
    tests[1] = "12.0 * (24 * (12.00 / 24))";

    tests[2] = "10.0 - 21";
    tests[3] = "0.1112 - (10 + (10.0 - 21))";


    tests[4] = "(20 + 10) * lg(100)";
    tests[5] = "20.0 * 12.0 / 100.0 * (100.0 + 20.0) * 5.0 - lg( 85.0+(20 - 1 * 5))";

    TextCalc::Do(tests[0]);
    TextCalc::Do(tests[1]);

    TextCalc::Do(tests[2]);
    TextCalc::Do(tests[3]);

    TextCalc::Do(tests[4]);
    TextCalc::Do(tests[5]);

    CHECK(std::stod(tests[0]) == 0.5);
    CHECK(std::stod(tests[1]) == 144);

    CHECK(std::stod(tests[2]) == -11);
    CHECK(std::stod(tests[3]) == 1.1112);

    CHECK(std::stod(tests[4]) == 60);
    CHECK(std::stod(tests[5]) == 1438.0);
}