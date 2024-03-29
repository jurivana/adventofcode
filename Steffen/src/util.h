// cmake -G "MinGW Makefiles" ..
// make -j | .\aoc.exe

#pragma once

#include <fstream>
#include <iostream>
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
