#pragma once

#include "util.h"

void aoc04() {
    std::vector<std::string> input = read("../input/04.txt");
    std::vector<std::vector<std::vector<int>>> sections;
    for (int i = 0; i < input.size(); i++) {
        sections.push_back(std::vector<std::vector<int>>(2));
        for (int j = 0; j < 2; j++) {
            sections[i][j] = std::vector<int>(2);
        }
        size_t pos = input[i].find("-");
        sections[i][0][0] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 1);
        pos = input[i].find(",");
        sections[i][0][1] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 1);
        pos = input[i].find("-");
        sections[i][1][0] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 1);
        sections[i][1][1] = std::stoi(input[i]);
    }
    int cnt = 0;
    int cnt2 = 0;
    for (int i = 0; i < sections.size(); i++) {
        // std::cout << sections[i][0][0] << " " << sections[i][0][1] << " | " << sections[i][1][0] << " " << sections[i][1][1] << std::endl;
        if ((sections[i][0][0] >= sections[i][1][0] && sections[i][0][1] <= sections[i][1][1]) ||
            (sections[i][0][0] <= sections[i][1][0] && sections[i][0][1] >= sections[i][1][1])) {
            cnt++;
            cnt2++;
        } else if ((sections[i][0][0] >= sections[i][1][0] && sections[i][0][0] <= sections[i][1][1]) ||
                   (sections[i][0][1] >= sections[i][1][0] && sections[i][0][1] <= sections[i][1][1])) {
            cnt2++;
        }
    }
    std::cout << cnt << std::endl;
    std::cout << cnt2 << std::endl;
}
