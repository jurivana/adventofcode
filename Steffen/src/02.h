#pragma once

#include "util.h"

void aoc02() {
    std::vector<std::string> input = read("../input/02.txt");
    int score = 0;
    int score2 = 0;
    for (int i = 0; i < input.size(); i++) {
        int a = input[i].at(0) - 'A';
        int x = input[i].at(2) - 'X';
        score += x + 1;
        if (a == x) {
            score += 3;
        }
        if ((a + 1) % 3 == x) {
            score += 6;
        }

        int b = (a + x + 2) % 3;
        score2 += b + 1;
        if (a == b) {
            score2 += 3;
        }
        if ((a + 1) % 3 == b) {
            score2 += 6;
        }
    }
    std::cout << score << std::endl;
    std::cout << score2 << std::endl;
}
