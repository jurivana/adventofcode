#pragma once

#include "util.h"

int priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

void aoc03() {
    std::vector<std::string> input = read("../input/03.txt");
    int sum = 0;
    std::vector<std::vector<bool>> rucksacks;
    for (int i = 0; i < input.size(); i++) {
        std::vector<bool> compartment(53, false);
        for (int j = 0; j < input[i].size() / 2; j++) {
            compartment[priority(input[i].at(j))] = true;
        }
        bool found = false;
        std::vector<bool> rucksack = compartment;
        for (int j = input[i].size() / 2; j < input[i].size(); j++) {
            int prio = priority(input[i].at(j));
            if (compartment[prio] && !found) {
                sum += prio;
                found = true;
            }
            rucksack[prio] = true;
        }
        rucksacks.push_back(rucksack);
    }
    std::cout << sum << std::endl;
    
    int sum2 = 0;
    for (int i = 0; i < rucksacks.size() / 3; i++) {
        std::vector<bool> conjunction(53, true);
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 53; k++) {
                conjunction[k] = conjunction[k] && rucksacks[3 * i + j][k];
            }
        }
        for (int j = 0; j < 53; j++) {
            if (conjunction[j]) {
                sum2 += j;
            }
        }
    }
    std::cout << sum2 << std::endl;
}
