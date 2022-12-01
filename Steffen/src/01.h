#pragma once

#include "util.h"

void aoc01() {
    std::vector<std::string> input = read("../input/01.txt");
    std::vector<std::vector<int>> elves;
    std::vector<int> elf;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "") {
            elves.push_back(elf);
            elf.clear();
        } else {
            elf.push_back(std::stoi(input[i]));
        }
    }
    elves.push_back(elf);

    int max = 0;
    std::vector<int> sums;
    for (int i = 0; i < elves.size(); i++) {
        int sum = 0;
        for (int j = 0; j < elves[i].size(); j++) {
            sum += elves[i][j];
        }
        if (sum > max) {
            max = sum;
        }
        sums.push_back(sum);
    }
    std::cout << max << std::endl;

    std::sort(sums.begin(), sums.end());
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += sums[sums.size() - 1 - i];
    }
    std::cout << sum << std::endl;
}
