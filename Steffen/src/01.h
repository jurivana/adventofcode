#pragma once

#include "util.h"

void aoc01() {
    std::vector<std::string> input = read("../input/test.txt");
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i] << std::endl;
    }
}
