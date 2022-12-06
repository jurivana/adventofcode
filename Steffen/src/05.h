#pragma once

#include "util.h"

void aoc05() {
    std::vector<std::string> input = read("../input/05.txt");
    int n_stacks = 9;
    int height = 8;
    std::vector<std::stack<char>> crates(n_stacks);
    std::vector<std::stack<char>> crates2(n_stacks);
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < n_stacks; j++) {
            char crate = input[i].at(4 * j + 1);
            if (crate != ' ') {
                crates[j].push(crate);
                crates2[j].push(crate);
            }
        }
    }
    for (int i = 10; i < input.size(); i++) {
        input[i].erase(0, 5); // move_
        int pos = input[i].find(" ");
        int n = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 6); // _from_
        pos = input[i].find(" ");
        int from = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 4); // _to_
        pos = input[i].find(" ");
        int to = std::stoi(input[i]);
        std::stack<char> tmp;
        for (int j = 0; j < n; j++) {
            crates[to - 1].push(crates[from - 1].top());
            crates[from - 1].pop();

            tmp.push(crates2[from - 1].top());
            crates2[from - 1].pop();
        }
        while (!tmp.empty()) {
            crates2[to - 1].push(tmp.top());
            tmp.pop();
        }
    }
    for (int i = 0; i < n_stacks; i++) {
        std::cout << crates[i].top();
    }
    std::cout << std::endl;
    for (int i = 0; i < n_stacks; i++) {
        std::cout << crates2[i].top();
    }
    std::cout << std::endl;
}
