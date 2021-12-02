#include <fstream>
#include <iostream>
#include <vector>

int aoc1() {
    // std::ifstream file("input/input.txt");
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

    std::ifstream file("input/input.txt");
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

int main() {
    std::cout << aoc1() << std::endl;
}
