#pragma once

#include "util.h"

void aoc16() {
    std::vector<std::string> input = read("../input/test.txt");
    int n = input.size();
    std::map<std::string, int> label_map;
    std::vector<int> flow_rates(n);
    std::vector<std::vector<std::string>> neighbor_labels(n);
    int start = -1;
    for (int i = 0; i < n; i++) {
        input[i].erase(0, 6);
        label_map.insert({input[i].substr(0, 2), i});
        if (input[i].substr(0, 2) == "AA") {
            start = i;
        }
        input[i].erase(0, 17);
        int pos = input[i].find(";");
        flow_rates[i] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 24);
        if (input[i].at(0) == ' ') {
            input[i].erase(0, 1);
        }
        bool end = false;
        while (!end) {
            pos = input[i].find(",");
            if (pos == std::string::npos) {
                pos = input[i].size();
                end = true;
            }
            neighbor_labels[i].push_back(input[i].substr(0, pos));
            input[i].erase(0, pos + 2);
        }
    }
    std::vector<std::vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = std::vector<int>(n, std::numeric_limits<int>::max());
        for (int j = 0; j < neighbor_labels[i].size(); j++) {
            a[i][label_map[neighbor_labels[i][j]]] = 1;
        }
        a[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
