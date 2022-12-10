#pragma once

#include "util.h"

int n_tail_positions(std::vector<std::string> input, int length) {
    std::vector<std::vector<int>> rope(length);
    for (int i = 0; i < length; i++) {
        rope[i] = {0, 0};
    }
    std::map<char, std::vector<int>> dirs = {{'R', {1, 0}}, {'L', {-1, 0}}, {'U', {0, 1}}, {'D', {0, -1}}};
    std::set<std::vector<int>> tail_positions;
    for (int i = 0; i < input.size(); i++) {
        std::vector<int> dir = dirs[input[i].at(0)];
        input[i].erase(0, 2);
        int n = std::stoi(input[i]);
        for (int j = 0; j < n; j++) {
            rope[0] = add(rope[0], dir);
            for (int k = 1; k < length; k++) {
                std::vector<int> offset = sub(rope[k - 1], rope[k]);
                bool keep_up = false;
                for (int l = 0; l < 2; l++) {
                    if (std::abs(offset[l]) == 2) {
                        keep_up = true;
                        offset[l] /= 2;
                    }
                }
                if (keep_up) {
                    rope[k] = add(rope[k], offset);
                }
                tail_positions.insert(rope[length - 1]);
            }
        }
    }
    return tail_positions.size();
}

void aoc09() {
    std::vector<std::string> input = read("../input/09.txt");
    std::cout << n_tail_positions(input, 2) << std::endl;
    std::cout << n_tail_positions(input, 10) << std::endl;
}
