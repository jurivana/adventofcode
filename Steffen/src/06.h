#pragma once

#include "util.h"

int first_n_distinct(std::string input, int n) {
    for (int i = n; i <= input.size(); i++) {
        std::set<char> distincts;
        for (int j = 0; j < n; j++) {
            distincts.insert(input.at(i - n + j));
        }
        if (distincts.size() == n) {
            return i;
        }
    }
    return 0;
}

void aoc06() {
    std::vector<std::string> input = read("../input/06.txt");
    std::cout << first_n_distinct(input[0], 4) << std::endl;
    std::cout << first_n_distinct(input[0], 14) << std::endl;
}
