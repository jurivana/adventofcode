#include <fstream>
#include <iostream>
#include <vector>

int aoc011() {
    std::ifstream file("input/1.txt");
    std::string line;
    std::getline(file, line);
    int last = std::stoi(line);
    int cnt = 0;
    while (std::getline(file, line)) {
        int curr = std::stoi(line);
        if (curr > last) {
            cnt++;
        }
        last = curr;
    }
    return cnt;
}

int aoc012() {
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

int aoc021() {
    std::ifstream file("input/2.txt");
    std::string line;
    int horizontal = 0;
    int depth = 0;
    while (std::getline(file, line)) {
        size_t pos = line.find(" ");
        std::string direction = line.substr(0, pos);
        line.erase(0, pos + 1);
        int step = std::stoi(line);
        if (direction == "forward") {
            horizontal += step;
        } else if (direction == "down") {
            depth += step;
        } else if (direction == "up") {
            depth -= step;
        }
    }
    return horizontal * depth;
}

int aoc022() {
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

int aoc031() {
    std::ifstream file("input/3.txt");
    std::string line;
    std::vector<int> ones(12);
    int cnt = 0;
    while (std::getline(file, line)) {
        for (size_t i = 0; i < 12; i++) {
            if (line.at(i) == '1') {
                ones[i]++;
            }
        }
        cnt++;
    }
    int gamma = 0;
    int epsilon = 0;
    for (size_t i = 0; i < 12; i++) {
        gamma <<= 1;
        epsilon <<= 1;
        if (ones[i] > cnt / 2) {
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }
    return gamma * epsilon;
}

int aoc032() {
    std::ifstream file("input/3.txt");
    std::string line;
    std::vector<std::vector<bool>> oxygen;
    std::vector<std::vector<bool>> co2;
    while (std::getline(file, line)) {
        std::vector<bool> bits(12);
        for (size_t i = 0; i < 12; i++) {
            bits[i] = line.at(i) == '1';
        }
        oxygen.push_back(bits);
        co2.push_back(bits);
    }
    for (size_t i = 0; i < 12; i++) {
        int cnt = 0;
        for (size_t j = 0; j < oxygen.size(); j++) {
            if (oxygen[j][i]) {
                cnt++;
            }
        }
        bool most_common = cnt >= oxygen.size() - cnt;
        for (size_t j = 0; j < oxygen.size(); j++) {
            if (oxygen[j][i] != most_common) {
                oxygen.erase(oxygen.begin() + j);
                j--;
            }
        }
    }
    for (size_t i = 0; i < 12 && co2.size() > 1; i++) {
        int cnt = 0;
        for (size_t j = 0; j < co2.size(); j++) {
            if (co2[j][i]) {
                cnt++;
            }
        }
        bool least_common = cnt < co2.size() - cnt;
        for (size_t j = 0; j < co2.size(); j++) {
            if (co2[j][i] != least_common) {
                co2.erase(co2.begin() + j);
                j--;
            }
        }
    }
    int gamma = 0;
    int epsilon = 0;
    for (size_t i = 0; i < 12; i++) {
        gamma <<= 1;
        epsilon <<= 1;
        if (oxygen[0][i]) {
            gamma += 1;
        }
        if (co2[0][i]) {
            epsilon += 1;
        }
    }
    return gamma * epsilon;
}

int main() {
    std::cout << aoc032() << std::endl;
}
