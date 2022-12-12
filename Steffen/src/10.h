#pragma once

#include "util.h"

void aoc10() {
    std::vector<std::string> input = read("../input/10.txt");
    int x = 1;
    int n_ticks = 0;
    std::vector<int> signal_strengths;
    std::vector<bool> image;
    auto tick = [&]() {
        n_ticks++;
        if ((n_ticks + 20) % 40 == 0) {
            signal_strengths.push_back(n_ticks * x);
        }

        image.push_back(std::abs(n_ticks % 40 - x - 1) <= 1);
    };
    for (int i = 0; i < input.size(); i++) {
        std::string operation = input[i].substr(0, 4);
        if (operation == "addx") {
            for (int j = 0; j < 2; j++) {
                tick();
            }
            input[i].erase(0, 4);
            x += std::stoi(input[i]);
        } else {
            tick();
        }
    }
    int sum = 0;
    for (int i = 0; i < signal_strengths.size(); i++) {
        sum += signal_strengths[i];
    }
    std::cout << sum << std::endl;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            std::cout << (image[40 * i + j] ? "#" : ".");
        }
        std::cout << std::endl;
    }
}
