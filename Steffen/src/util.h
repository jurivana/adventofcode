// cmake -G "MinGW Makefiles" ..
// make -j | .\aoc.exe

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

std::vector<std::string> read(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<int> add(std::vector<int> a, std::vector<int> b) {
    if (a.size() != b.size()) {
        std::cout << "ERROR: Vector addition size mismatch" << std::endl;
    }
    std::vector<int> sum(a.size());
    for (int i = 0; i < a.size(); i++) {
        sum[i] = a[i] + b[i];
    }
    return sum;
}

std::vector<int> sub(std::vector<int> a, std::vector<int> b) {
    if (a.size() != b.size()) {
        std::cout << "ERROR: Vector subtraction size mismatch" << std::endl;
    }
    std::vector<int> diff(a.size());
    for (int i = 0; i < a.size(); i++) {
        diff[i] = a[i] - b[i];
    }
    return diff;
}
