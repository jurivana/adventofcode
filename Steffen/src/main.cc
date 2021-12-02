#include <fstream>
#include <iostream>
#include <vector>

int aoc1() {
    // std::ifstream file("input/1.txt");
    // std::string line;
    // std::getline(file, line);
    // int last = std::stoi(line);
    // int cnt = 0;
    // while (std::getline(file, line)) {
    //     int curr = std::stoi(line);
    //     if (curr > last) {
    //         cnt++;
    //     }
    //     last = curr;
    // }
    // return cnt;

    std::ifstream file("input/1.txt");
    std::string line;
    std::vector<int> input;
    while (std::getline(file, line)) {
        input.push_back(std::stoi(line));
    }
    int last = input[0] + input[1] + input[2];
    int cnt = 0;
    for (size_t i = 1; i < input.size() - 2; i++) {
        int curr = input[i] + input[i + 1] + input[i + 2];
        if (curr > last) {
            cnt++;
        }
        last = curr;
    }
    return cnt;
}

int aoc2() {
    // std::ifstream file("input/2.txt");
    // std::string line;
    // int horizontal = 0;
    // int depth = 0;
    // while (std::getline(file, line)) {
    //     size_t pos = line.find(" ");
    //     std::string direction = line.substr(0, pos);
    //     line.erase(0, pos + 1);
    //     int step = std::stoi(line);
    //     if (direction == "forward") {
    //         horizontal += step;
    //     } else if (direction == "down") {
    //         depth += step;
    //     } else if (direction == "up") {
    //         depth -= step;
    //     }
    // }
    // return horizontal * depth;

    std::ifstream file("input/2.txt");
    std::string line;
    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    while (std::getline(file, line)) {
        size_t pos = line.find(" ");
        std::string direction = line.substr(0, pos);
        line.erase(0, pos + 1);
        int step = std::stoi(line);
        if (direction == "forward") {
            horizontal += step;
            depth += step * aim;
        } else if (direction == "down") {
            aim += step;
        } else if (direction == "up") {
            aim -= step;
        }
    }
    return horizontal * depth;
}

int main() {
    std::cout << aoc2() << std::endl;
}
