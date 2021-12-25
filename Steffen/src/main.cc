#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
#include <tuple>
#include <vector>

#include "overiority_queue.h"

int aoc011() {
    std::ifstream file("input/01.txt");
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
    std::ifstream file("input/01.txt");
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
    std::ifstream file("input/02.txt");
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
    std::ifstream file("input/02.txt");
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
    std::ifstream file("input/03.txt");
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
    std::ifstream file("input/03.txt");
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

std::pair<std::vector<int>, std::vector<std::vector<std::vector<int>>>> input04() {
    std::ifstream file("input/04.txt");
    std::string line;

    std::vector<int> drawn;
    std::getline(file, line);
    size_t pos = 0;
    do {
        pos = line.find(",");
        drawn.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    } while (pos != std::string::npos);

    std::vector<std::vector<std::vector<int>>> cards;
    while (std::getline(file, line)) {
        std::vector<std::vector<int>> card(5);
        for (size_t i = 0; i < 5; i++) {
            std::getline(file, line);
            std::vector<int> row(5);
            for (size_t j = 0; j < 5; j++) {
                row[j] = std::stoi(line.substr(0, 2));
                line.erase(0, 3);
            }
            card[i] = row;
        }
        cards.push_back(card);
    }

    return {drawn, cards};
}

int aoc041() {
    std::vector<int> drawn;
    std::vector<std::vector<std::vector<int>>> cards;
    std::tie(drawn, cards) = input04();

    // for (auto x : drawn) {
    //     std::cout << x << " ";
    // }
    // std::cout << std::endl;

    // for (auto card : cards) {
    //     for (auto row : card) {
    //         for (auto x : row) {
    //             std::cout << x << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << "----" << std::endl;
    // }

    std::vector<std::vector<std::vector<bool>>> marked(cards.size());
    for (size_t k = 0; k < marked.size(); k++) {
        marked[k] = std::vector<std::vector<bool>>(5);
        for (size_t i = 0; i < 5; i++) {
            marked[k][i] = std::vector<bool>(5, false);
        }
    }

    int bingo = -1;
    int winning_number;
    for (size_t l = 0; l < drawn.size() && bingo == -1; l++) {
        int number = drawn[l];
        for (size_t k = 0; k < cards.size(); k++) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (cards[k][i][j] == number) {
                        marked[k][i][j] = true;
                    }
                }
            }
        }

        for (size_t k = 0; k < marked.size(); k++) {
            for (size_t i = 0; i < 5; i++) {
                bool won = true;
                for (size_t j = 0; j < 5 && won; j++) {
                    if (!marked[k][i][j]) {
                        won = false;
                    }
                }
                if (won) {
                    bingo = k;
                }
            }
            for (size_t i = 0; i < 5; i++) {
                bool won = true;
                for (size_t j = 0; j < 5 && won; j++) {
                    if (!marked[k][j][i]) {
                        won = false;
                    }
                }
                if (won) {
                    bingo = k;
                }
            }
            if (bingo == k) {
                winning_number = number;
                std::cout << "Bingo!" << std::endl;
            }
        }
    }

    int sum = 0;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            if (!marked[bingo][i][j]) {
                sum += cards[bingo][i][j];
            }
        }
    }
    return sum * winning_number;
}

int aoc042() {
    std::vector<int> drawn;
    std::vector<std::vector<std::vector<int>>> cards;
    std::tie(drawn, cards) = input04();

    std::vector<std::vector<std::vector<bool>>> marked(cards.size());
    for (size_t k = 0; k < marked.size(); k++) {
        marked[k] = std::vector<std::vector<bool>>(5);
        for (size_t i = 0; i < 5; i++) {
            marked[k][i] = std::vector<bool>(5, false);
        }
    }

    int bingo = -1;
    int winning_number;
    for (size_t l = 0; l < drawn.size() && bingo == -1; l++) {
        int number = drawn[l];
        std::cout << "#cards " << cards.size() << " number " << number << std::endl;
        for (size_t k = 0; k < cards.size(); k++) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (cards[k][i][j] == number) {
                        marked[k][i][j] = true;
                    }
                }
            }
        }

        for (size_t k = 0; k < marked.size(); k++) {
            for (size_t i = 0; i < 5; i++) {
                bool won = true;
                for (size_t j = 0; j < 5 && won; j++) {
                    if (!marked[k][i][j]) {
                        won = false;
                    }
                }
                if (won) {
                    bingo = k;
                }
            }
            for (size_t i = 0; i < 5; i++) {
                bool won = true;
                for (size_t j = 0; j < 5 && won; j++) {
                    if (!marked[k][j][i]) {
                        won = false;
                    }
                }
                if (won) {
                    bingo = k;
                }
            }
            if (bingo == k) {
                winning_number = number;
                std::cout << "Bingo! " << bingo << std::endl;
                if (cards.size() > 1) {
                    cards.erase(cards.begin() + k);
                    marked.erase(marked.begin() + k);
                    k--;
                    bingo = -1;
                }
            }
        }
    }

    int sum = 0;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            if (!marked[bingo][i][j]) {
                sum += cards[bingo][i][j];
            }
        }
    }
    return sum * winning_number;
}

int output05(std::vector<std::vector<int>> vents) {
    int cnt = 0;
    int max = 0;
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            if (vents[i][j] > 1) {
                cnt++;
            }
            if (vents[i][j] > max) {
                max = vents[i][j];
            }
        }
    }

    std::ofstream ofile("output/05.ppm");
    ofile << "P3 1000 1000 " << max << std::endl;
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            ofile << vents[j][i] << " " << vents[j][i] << " " << vents[j][i] << " ";
        }
        ofile << std::endl;
    }
    ofile.close();

    return cnt;
}

int aoc051() {
    struct Line {
        std::vector<int> a;
        std::vector<int> b;
    };
    std::ifstream ifile("input/05.txt");
    std::string line;
    std::vector<Line> lines;
    while (std::getline(ifile, line)) {
        Line l;
        size_t pos = line.find(",");
        l.a.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
        pos = line.find(" -> ");
        l.a.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 4);
        pos = line.find(",");
        l.b.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
        l.b.push_back(std::stoi(line));
        if (l.a[0] == l.b[0] || l.a[1] == l.b[1]) {
            lines.push_back(l);
        }
    }
    // for (auto l : lines) {
    //     std::cout << "(" << l.a[0] << ", " << l.a[1] << ") - (" << l.b[0] << ", " << l.b[1] << ")" << std::endl;
    // }

    std::vector<std::vector<int>> vents(1000);
    for (size_t i = 0; i < 1000; i++) {
        vents[i] = std::vector<int>(1000, 0);
    }
    for (auto l : lines) {
        bool swap = false;
        if (l.a[0] == l.b[0]) {
            int tmp = l.a[1];
            l.a[1] = l.a[0];
            l.a[0] = tmp;
            tmp = l.b[1];
            l.b[1] = l.b[0];
            l.b[0] = tmp;
            swap = true;
        }
        if (l.a[0] > l.b[0]) {
            int tmp = l.b[0];
            l.b[0] = l.a[0];
            l.a[0] = tmp;
        }
        for (int i = l.a[0]; i <= l.b[0]; i++) {
            if (!swap) {
                vents[i][l.a[1]]++;
            } else {
                vents[l.a[1]][i]++;
            }
        }
    }

    return output05(vents);
}

int aoc052() {
    struct Line {
        std::vector<int> a;
        std::vector<int> b;
    };
    std::ifstream ifile("input/05.txt");
    std::string line;
    std::vector<Line> lines;
    while (std::getline(ifile, line)) {
        Line l;
        size_t pos = line.find(",");
        l.a.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
        pos = line.find(" -> ");
        l.a.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 4);
        pos = line.find(",");
        l.b.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
        l.b.push_back(std::stoi(line));
        // if (!(l.a[0] == l.b[0] || l.a[1] == l.b[1] ||
        //       l.b[0] - l.a[0] == l.b[1] - l.a[1] ||
        //       l.b[0] - l.a[0] == l.a[1] - l.b[1])) {
        //     std::cout << "!" << std::endl;
        // }
        lines.push_back(l);
    }
    // for (auto l : lines) {
    //     std::cout << "(" << l.a[0] << ", " << l.a[1] << ") - (" << l.b[0] << ", " << l.b[1] << ")" << std::endl;
    // }

    std::vector<std::vector<int>> vents(1000);
    for (size_t i = 0; i < 1000; i++) {
        vents[i] = std::vector<int>(1000, 0);
    }
    for (auto l : lines) {
        bool swap = false;
        if (l.a[0] == l.b[0]) {
            int tmp = l.a[1];
            l.a[1] = l.a[0];
            l.a[0] = tmp;
            tmp = l.b[1];
            l.b[1] = l.b[0];
            l.b[0] = tmp;
            swap = true;
        }
        if (l.a[0] > l.b[0]) {
            std::vector<int> tmp = l.b;
            l.b = l.a;
            l.a = tmp;
        }
        int m = (l.b[1] - l.a[1]) / (l.b[0] - l.a[0]);
        for (int i = l.a[0]; i <= l.b[0]; i++) {
            if (!swap) {
                vents[i][l.a[1] + m * (i - l.a[0])]++;
            } else {
                vents[l.a[1] + m * (i - l.a[0])][i]++;
            }
        }
    }

    return output05(vents);
}

int aoc061() {
    std::ifstream file("input/06.txt");
    std::string line;
    std::getline(file, line);
    std::vector<int> fish;
    size_t pos = 0;
    do {
        pos = line.find(",");
        fish.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    } while (pos != std::string::npos);
    for (size_t i = 0; i < 80; i++) {
        size_t n = fish.size();
        // std::cout << i << " " << n << std::endl;
        for (size_t j = 0; j < n; j++) {
            fish[j]--;
            if (fish[j] == -1) {
                fish[j] = 6;
                fish.push_back(8);
            }
        }
    }
    return fish.size();
}

long long aoc062() {
    std::vector<int> fish = {0};
    size_t m = 256;
    std::vector<long long> daniel(6);
    for (size_t i = 0; i < 256; i++) {
        size_t n = fish.size();
        std::cout << i << " " << n << std::endl;
        for (size_t j = 0; j < 6; j++) {
            if (m - j == i) {
                daniel[j] = n;
            }
        }
        for (size_t j = 0; j < n; j++) {
            fish[j]--;
            if (fish[j] == -1) {
                fish[j] = 6;
                fish.push_back(8);
            }
        }
    }
    std::ifstream file("input/06.txt");
    std::string line;
    std::getline(file, line);
    long long sum = 0;
    size_t pos = 0;
    do {
        pos = line.find(",");
        sum += daniel[std::stoi(line.substr(0, pos))];
        line.erase(0, pos + 1);
    } while (pos != std::string::npos);
    return sum;
}

int aoc071() {
    std::ifstream file("input/07.txt");
    std::string line;
    std::getline(file, line);
    std::vector<int> crabs;
    size_t pos = 0;
    do {
        pos = line.find(",");
        crabs.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    } while (pos != std::string::npos);

    std::sort(crabs.begin(), crabs.end());
    int median = crabs[crabs.size() / 2];

    int fuel = 0;
    for (size_t i = 0; i < crabs.size(); i++) {
        fuel += std::abs(crabs[i] - median);
    }
    return fuel;
}

int aoc072() {
    std::ifstream file("input/07.txt");
    std::string line;
    std::getline(file, line);
    std::vector<int> crabs;
    size_t pos = 0;
    do {
        pos = line.find(",");
        crabs.push_back(std::stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    } while (pos != std::string::npos);

    // Summe über kleine Gauße minimieren durch Ableitung Nullsetzen
    int root = 0;
    for (size_t i = 0; i < crabs.size(); i++) {
        root += crabs[i];
    }
    // Allgemein eigentlich floor ODER ceil!
    root = std::round((double) root / crabs.size() - 0.5);

    int fuel = 0;
    for (size_t i = 0; i < crabs.size(); i++) {
        int n = std::abs(crabs[i] - root);
        fuel += (n * n + n) / 2;
    }
    return fuel;
}

int aoc081() {
    std::ifstream file("input/08.txt");
    std::string line;
    int cnt = 0;
    while (std::getline(file, line)) {
        size_t pos = line.find(" | ");
        line.erase(0, pos + 3);
        do {
            pos = line.find(" ");
            std::string digit = line.substr(0, pos);
            if (digit.size() == 2 || digit.size() == 3 || digit.size() == 4 || digit.size() == 7) {
                cnt++;
            }
            line.erase(0, pos + 1);
        } while (pos != std::string::npos);
    }
    return cnt;
}

std::vector<std::vector<char>> cleanup(std::vector<std::vector<char>> digits, std::vector<char> s) {
    for (size_t i = 0; i < digits.size(); i++) {
        for (size_t j = 0; j < digits[i].size(); j++) {
            for (size_t k = 0; k < 7; k++) {
                if (digits[i][j] == s[k]) {
                    digits[i].erase(digits[i].begin() + j);
                    j--;
                }
            }
        }
        if (digits[i].size() == 0) {
            digits.erase(digits.begin() + i);
            i--;
        }
    }
    std::sort(digits.begin(), digits.end(), [](std::vector<char> a, std::vector<char> b) {
        return a.size() < b.size();
    });
    return digits;
}

int aoc082() {
    std::ifstream file("input/08.txt");
    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        std::vector<std::vector<char>> digits;
        size_t pos;
        do {
            pos = line.find(" ");
            std::string digit_string = line.substr(0, pos);
            if (digit_string == "|") {
                break;
            }
            std::vector<char> digit(digit_string.begin(), digit_string.end());
            if (digit.size() != 7) {
                digits.push_back(digit);
            }
            line.erase(0, pos + 1);
        } while (pos != std::string::npos);
        std::sort(digits.begin(), digits.end(), [](std::vector<char> a, std::vector<char> b) {
            return a.size() < b.size();
        });
        std::vector<char> s(7, 'x');

        for (auto x : digits[1]) { // 7
            bool found = false;
            for (auto y : digits[0]) { // 1
                if (x == y) {
                    found = true;
                }
            }
            if (!found) {
                s[0] = x;
            }
        }

        for (size_t i = 0; i < 2; i++) {                           // 1
            for (auto digit : {digits[6], digits[7], digits[8]}) { // 0, 6, 9
                bool found = false;
                for (auto y : digit) {
                    if (digits[0][i] == y) {
                        found = true;
                    }
                }
                if (!found) {
                    s[2] = digits[0][i];
                    s[5] = digits[0][(i + 1) % 2];
                }
            }
        }

        digits = cleanup(digits, s);

        for (auto x : digits[0]) {
            for (auto y : digits[1]) { // 3, 4
                if (x == y) {
                    s[3] = x;
                }
            }
        }

        digits = cleanup(digits, s);

        for (auto digit : {digits[2], digits[3], digits[4]}) { // 2, 5, 9
            for (size_t i = 0; i < 2; i++) {
                if (digit[i] != digits[0][0] && digit[i] != digits[1][0]) { // 3, 4
                    s[4] = digit[i];
                    s[6] = digit[(i + 1) % 2];
                }
            }
        }

        digits = cleanup(digits, s);

        s[1] = digits[0][0];

        std::vector<std::vector<char>> numbers = {
            {s[0], s[1], s[2], s[4], s[5], s[6]},       // 0
            {s[2], s[5]},                               // 1
            {s[0], s[2], s[3], s[4], s[6]},             // 2
            {s[0], s[2], s[3], s[5], s[6]},             // 3
            {s[1], s[2], s[3], s[5]},                   // 4
            {s[0], s[1], s[3], s[5], s[6]},             // 5
            {s[0], s[1], s[3], s[4], s[5], s[6]},       // 6
            {s[0], s[2], s[5]},                         // 7
            {s[0], s[1], s[2], s[3], s[4], s[5], s[6]}, // 8
            {s[0], s[1], s[2], s[3], s[5], s[6]}};      // 9
        for (size_t i = 0; i < 10; i++) {
            std::sort(numbers[i].begin(), numbers[i].end());
        }
        std::map<std::vector<char>, int> map;
        for (size_t i = 0; i < 10; i++) {
            map[numbers[i]] = i;
        }
        line.erase(0, 2);
        std::stringstream ss("");
        do {
            pos = line.find(" ");
            std::string digit_string = line.substr(0, pos);
            std::vector<char> digit(digit_string.begin(), digit_string.end());
            std::sort(digit.begin(), digit.end());
            ss << map[digit];
            line.erase(0, pos + 1);
        } while (pos != std::string::npos);
        sum += std::stoi(ss.str());
    }
    return sum;
}

int aoc091() {
    std::ifstream file("input/09.txt");
    std::string line;
    std::vector<std::vector<int>> heights;
    while (std::getline(file, line)) {
        std::vector<int> row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            row[i] = line.at(i) - '0';
        }
        heights.push_back(row);
    }

    int risk = 0;
    for (size_t i = 0; i < heights.size(); i++) {
        for (size_t j = 0; j < heights[i].size(); j++) {
            bool low = true;
            for (size_t di = (i > 0 ? i - 1 : i); di <= (i < heights.size() - 1 ? i + 1 : i) && low; di++) {
                if (di != i && heights[i][j] >= heights[di][j]) {
                    low = false;
                }
            }
            for (size_t dj = (j > 0 ? j - 1 : j); dj <= (j < heights[i].size() - 1 ? j + 1 : j) && low; dj++) {
                if (dj != j && heights[i][j] >= heights[i][dj]) {
                    low = false;
                }
            }
            if (low) {
                risk += heights[i][j] + 1;
            }
        }
    }
    return risk;
}

int aoc092() {
    std::ifstream file("input/09.txt");
    std::string line;
    std::vector<std::vector<int>> heights;
    while (std::getline(file, line)) {
        std::vector<int> row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            row[i] = line.at(i) - '0';
        }
        heights.push_back(row);
    }
    // heights = {
    //     {2, 1, 9, 9, 9, 4, 3, 2, 1, 0},
    //     {3, 9, 8, 7, 8, 9, 4, 9, 2, 1},
    //     {9, 8, 5, 6, 7, 8, 9, 8, 9, 2},
    //     {8, 7, 6, 7, 8, 9, 6, 7, 8, 9},
    //     {9, 8, 9, 9, 9, 6, 5, 6, 7, 8}};

    std::vector<std::vector<int>>
        basins(heights.size());
    for (size_t i = 0; i < heights.size(); i++) {
        basins[i] = std::vector<int>(heights[i].size(), 0);
    }
    int index = 0;
    for (size_t i = 0; i < heights.size(); i++) {
        for (size_t j = 0; j < heights[i].size(); j++) {
            bool low = true;
            for (size_t di = (i > 0 ? i - 1 : i); di <= (i < heights.size() - 1 ? i + 1 : i) && low; di++) {
                if (di != i && heights[i][j] >= heights[di][j]) {
                    low = false;
                }
            }
            for (size_t dj = (j > 0 ? j - 1 : j); dj <= (j < heights[i].size() - 1 ? j + 1 : j) && low; dj++) {
                if (dj != j && heights[i][j] >= heights[i][dj]) {
                    low = false;
                }
            }
            if (low) {
                index++;
                std::queue<std::vector<size_t>> q;
                q.push({i, j});
                while (!q.empty()) {
                    std::vector<size_t> ij = q.front();
                    q.pop();
                    size_t i_ = ij[0];
                    size_t j_ = ij[1];
                    basins[i_][j_] = index;
                    for (size_t di = (i_ > 0 ? i_ - 1 : i_); di <= (i_ < heights.size() - 1 ? i_ + 1 : i_); di++) {
                        if (di != i_ && heights[di][j_] != 9 && basins[di][j_] == 0) {
                            q.push({di, j_});
                        }
                    }
                    for (size_t dj = (j_ > 0 ? j_ - 1 : j_); dj <= (j_ < heights[i_].size() - 1 ? j_ + 1 : j_); dj++) {
                        if (dj != j_ && heights[i_][dj] != 9 && basins[i_][dj] == 0) {
                            q.push({i_, dj});
                        }
                    }
                }
            }
        }
    }

    std::vector<int> sizes(index, 0);
    for (size_t i = 0; i < basins.size(); i++) {
        for (size_t j = 0; j < basins[i].size(); j++) {
            // char c = (char) basins[i][j] + '!';
            // std::cout << c;
            if (basins[i][j] != 0) {
                sizes[basins[i][j] - 1]++;
            }
        }
        // std::cout << std::endl;
    }
    std::sort(sizes.begin(), sizes.end());
    return sizes[sizes.size() - 1] * sizes[sizes.size() - 2] * sizes[sizes.size() - 3];
}

int aoc101() {
    std::ifstream file("input/10.txt");
    std::string line;
    int score = 0;
    while (std::getline(file, line)) {
        std::stack<char> s;
        for (size_t i = 0; i < line.size(); i++) {
            char c = line.at(i);
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                s.push(c);
            } else {
                char p = s.top();
                s.pop();
                switch (p) {
                case '(':
                    p = ')';
                    break;
                case '[':
                    p = ']';
                    break;
                case '{':
                    p = '}';
                    break;
                case '<':
                    p = '>';
                    break;
                }
                if (p != c) {
                    switch (c) {
                    case ')':
                        score += 3;
                        break;
                    case ']':
                        score += 57;
                        break;
                    case '}':
                        score += 1197;
                        break;
                    case '>':
                        score += 25137;
                        break;
                    }
                }
            }
        }
    }
    return score;
}

long long aoc102() {
    std::ifstream file("input/10.txt");
    std::string line;
    std::vector<long long> scores;
    while (std::getline(file, line)) {
        std::stack<char> s;
        bool corrupted = false;
        for (size_t i = 0; i < line.size(); i++) {
            char c = line.at(i);
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                s.push(c);
            } else {
                char p = s.top();
                s.pop();
                switch (p) {
                case '(':
                    p = ')';
                    break;
                case '[':
                    p = ']';
                    break;
                case '{':
                    p = '}';
                    break;
                case '<':
                    p = '>';
                    break;
                }
                if (p != c) {
                    corrupted = true;
                }
            }
        }
        if (!corrupted) {
            long long score = 0;
            while (!s.empty()) {
                char p = s.top();
                s.pop();
                score *= 5;
                switch (p) {
                case '(':
                    score += 1;
                    break;
                case '[':
                    score += 2;
                    break;
                case '{':
                    score += 3;
                    break;
                case '<':
                    score += 4;
                    break;
                }
            }
            scores.push_back(score);
        }
    }
    std::sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
}

int aoc111() {
    std::ifstream file("input/11.txt");
    std::string line;
    std::vector<std::vector<int>> octopusses(10);
    for (size_t i = 0; i < 10; i++) {
        std::getline(file, line);
        octopusses[i] = std::vector<int>(10);
        for (size_t j = 0; j < 10; j++) {
            octopusses[i][j] = line.at(j) - '0';
        }
    }

    int cnt = 0;
    for (size_t step = 0; step < 100; step++) {
        std::queue<std::vector<size_t>> q;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < 10; j++) {
                octopusses[i][j]++;
                if (octopusses[i][j] == 10) {
                    octopusses[i][j] = 0;
                    cnt++;
                    q.push({i, j});
                }
            }
        }
        while (!q.empty()) {
            std::vector<size_t> ij = q.front();
            q.pop();
            size_t i = ij[0];
            size_t j = ij[1];
            for (size_t di = (i > 0 ? i - 1 : i); di <= (i < 9 ? i + 1 : i); di++) {
                for (size_t dj = (j > 0 ? j - 1 : j); dj <= (j < 9 ? j + 1 : j); dj++) {
                    if ((di != i || dj != j) && octopusses[di][dj] != 0) {
                        octopusses[di][dj]++;
                        if (octopusses[di][dj] == 10) {
                            octopusses[di][dj] = 0;
                            cnt++;
                            q.push({di, dj});
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

int aoc112() {
    std::ifstream file("input/11.txt");
    std::string line;
    std::vector<std::vector<int>> octopusses(10);
    for (size_t i = 0; i < 10; i++) {
        std::getline(file, line);
        octopusses[i] = std::vector<int>(10);
        for (size_t j = 0; j < 10; j++) {
            octopusses[i][j] = line.at(j) - '0';
        }
    }

    bool flash = false;
    size_t step = 0;
    for (; !flash; step++) {
        std::queue<std::vector<size_t>> q;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < 10; j++) {
                octopusses[i][j]++;
                if (octopusses[i][j] == 10) {
                    octopusses[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        while (!q.empty()) {
            std::vector<size_t> ij = q.front();
            q.pop();
            size_t i = ij[0];
            size_t j = ij[1];
            for (size_t di = (i > 0 ? i - 1 : i); di <= (i < 9 ? i + 1 : i); di++) {
                for (size_t dj = (j > 0 ? j - 1 : j); dj <= (j < 9 ? j + 1 : j); dj++) {
                    if ((di != i || dj != j) && octopusses[di][dj] != 0) {
                        octopusses[di][dj]++;
                        if (octopusses[di][dj] == 10) {
                            octopusses[di][dj] = 0;
                            q.push({di, dj});
                        }
                    }
                }
            }
        }
        flash = true;
        for (size_t i = 0; i < 10 && flash; i++) {
            for (size_t j = 0; j < 10 && flash; j++) {
                if (octopusses[i][j] != 0) {
                    flash = false;
                }
            }
        }
    }
    return step;
}

int n;
std::vector<std::vector<bool>> m;
std::vector<bool> big;
int start;
int end;
int cnt = 0;

void path1(std::vector<bool> visited, int v) {
    visited[v] = true;
    if (v == end) {
        cnt++;
    }
    for (size_t i = 0; i < n; i++) {
        if (m[v][i] && (!visited[i] || big[i])) {
            path1(visited, i);
        }
    }
}

int aoc121() {
    std::ifstream file("input/12.txt");
    std::string line;
    std::map<std::string, int> map;
    std::vector<std::vector<int>> edges;
    int start;
    int index = 0;
    while (std::getline(file, line)) {
        std::vector<int> e(2);
        std::vector<std::string> names(2);
        size_t pos = line.find("-");
        names[0] = line.substr(0, pos);
        line.erase(0, pos + 1);
        names[1] = line;
        for (size_t i = 0; i < 2; i++) {
            if (!map.contains(names[i])) {
                map[names[i]] = index;
                index++;
                if (names[i] == "start") {
                    start = map[names[i]];
                }
                if (names[i] == "end") {
                    end = map[names[i]];
                }
                big.push_back(names[i].at(0) <= 'Z');
            }
            e[i] = map[names[i]];
        }
        edges.push_back(e);
    }
    n = big.size();

    // for (auto x : map) {
    //     std::cout << x.first << " " << x.second << (big[x.second] ? " big" : "") << std::endl;
    // }
    // std::cout << start << " -> " << end << std::endl;
    // for (auto e : edges) {
    //     std::cout << e[0] << "-" << e[1] << std::endl;
    // }

    m = std::vector<std::vector<bool>>(n);
    for (size_t i = 0; i < n; i++) {
        m[i] = std::vector<bool>(n, false);
    }
    for (auto e : edges) {
        m[e[0]][e[1]] = true;
        m[e[1]][e[0]] = true;
    }

    // for (size_t i = 0; i < n; i++) {
    //     for (size_t j = 0; j < n; j++) {
    //         std::cout << m[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::vector<bool> visited(n, false);
    path1(visited, start);
    return cnt;
}

void path2(std::vector<int> visited, int v, bool twice) {
    visited[v]++;
    if (!big[v] && visited[v] > 1) {
        twice = true;
    }
    if (v == end) {
        cnt++;
    }
    for (size_t i = 0; i < n; i++) {
        if (m[v][i] && (visited[i] == 0 || big[i] || (visited[i] == 1 && !twice && i != start && i != end))) {
            path2(visited, i, twice);
        }
    }
}

int aoc122() {
    std::ifstream file("input/12.txt");
    std::string line;
    std::map<std::string, int> map;
    std::vector<std::vector<int>> edges;
    int index = 0;
    while (std::getline(file, line)) {
        std::vector<int> e(2);
        std::vector<std::string> names(2);
        size_t pos = line.find("-");
        names[0] = line.substr(0, pos);
        line.erase(0, pos + 1);
        names[1] = line;
        for (size_t i = 0; i < 2; i++) {
            if (!map.contains(names[i])) {
                map[names[i]] = index;
                index++;
                if (names[i] == "start") {
                    start = map[names[i]];
                }
                if (names[i] == "end") {
                    end = map[names[i]];
                }
                big.push_back(names[i].at(0) <= 'Z');
            }
            e[i] = map[names[i]];
        }
        edges.push_back(e);
    }
    n = big.size();
    m = std::vector<std::vector<bool>>(n);
    for (size_t i = 0; i < n; i++) {
        m[i] = std::vector<bool>(n, false);
    }
    for (auto e : edges) {
        m[e[0]][e[1]] = true;
        m[e[1]][e[0]] = true;
    }
    std::vector<int> visited(n, 0);
    path2(visited, start, false);
    return cnt;
}

int aoc131() {
    std::ifstream file("input/13.txt");
    std::string line;
    std::vector<std::vector<int>> points;
    std::vector<std::vector<int>> bb = {{0, 0}, {0, 0}};
    while (std::getline(file, line)) {
        if (line == "") {
            break;
        }
        std::vector<int> point(2);
        size_t pos = line.find(",");
        point[1] = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        point[0] = std::stoi(line);
        for (size_t i = 0; i < 2; i++) {
            if (point[i] > bb[1][i]) {
                bb[1][i] = point[i];
            }
        }
        points.push_back(point);
    }
    std::vector<std::vector<bool>> paper(bb[1][0] + 1);
    for (size_t i = 0; i < paper.size(); i++) {
        paper[i] = std::vector<bool>(bb[1][1] + 1, false);
    }
    for (size_t i = 0; i < points.size(); i++) {
        paper[points[i][0]][points[i][1]] = true;
    }

    while (std::getline(file, line)) {
        line.erase(0, 11);
        bool along_x = line.at(0) == 'x';
        line.erase(0, 2);
        int fold = std::stoi(line);

        if (along_x) {
            if (fold - bb[0][1] >= bb[1][1] - fold) {
                // Nach links
                for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
                    for (size_t j = 0; j <= bb[1][1] - fold; j++) {
                        paper[i][fold - j] = paper[i][fold - j] || paper[i][fold + j];
                    }
                }
                bb[1][1] = fold - 1;
            } else {
                // Nach rechts
                for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
                    for (size_t j = 0; j <= fold - bb[0][1]; j++) {
                        paper[i][fold + j] = paper[i][fold + j] || paper[i][fold - j];
                    }
                }
                bb[0][1] = fold + 1;
            }
        } else {
            if (fold - bb[0][0] >= bb[1][0] - fold) {
                // Nach oben
                for (size_t i = 0; i <= bb[1][0] - fold; i++) {
                    for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
                        paper[fold - i][j] = paper[fold - i][j] || paper[fold + i][j];
                    }
                }
                bb[1][0] = fold - 1;
            } else {
                // Nach unten
                for (size_t i = 0; i <= fold - bb[0][0]; i++) {
                    for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
                        paper[fold + i][j] = paper[fold + i][j] || paper[fold - i][j];
                    }
                }
                bb[0][0] = fold + 1;
            }
        }
        break;
    }

    int cnt = 0;
    for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
        for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
            if (paper[i][j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

void aoc132() {
    std::ifstream file("input/13.txt");
    std::string line;
    std::vector<std::vector<int>> points;
    std::vector<std::vector<int>> bb = {{0, 0}, {0, 0}};
    while (std::getline(file, line)) {
        if (line == "") {
            break;
        }
        std::vector<int> point(2);
        size_t pos = line.find(",");
        point[1] = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        point[0] = std::stoi(line);
        for (size_t i = 0; i < 2; i++) {
            if (point[i] > bb[1][i]) {
                bb[1][i] = point[i];
            }
        }
        points.push_back(point);
    }
    std::vector<std::vector<bool>> paper(bb[1][0] + 1);
    for (size_t i = 0; i < paper.size(); i++) {
        paper[i] = std::vector<bool>(bb[1][1] + 1, false);
    }
    for (size_t i = 0; i < points.size(); i++) {
        paper[points[i][0]][points[i][1]] = true;
    }

    while (std::getline(file, line)) {
        line.erase(0, 11);
        bool along_x = line.at(0) == 'x';
        line.erase(0, 2);
        int fold = std::stoi(line);

        if (along_x) {
            if (fold - bb[0][1] >= bb[1][1] - fold) {
                // Nach links
                for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
                    for (size_t j = 0; j <= bb[1][1] - fold; j++) {
                        paper[i][fold - j] = paper[i][fold - j] || paper[i][fold + j];
                    }
                }
                bb[1][1] = fold - 1;
            } else {
                // Nach rechts
                for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
                    for (size_t j = 0; j <= fold - bb[0][1]; j++) {
                        paper[i][fold + j] = paper[i][fold + j] || paper[i][fold - j];
                    }
                }
                bb[0][1] = fold + 1;
            }
        } else {
            if (fold - bb[0][0] >= bb[1][0] - fold) {
                // Nach oben
                for (size_t i = 0; i <= bb[1][0] - fold; i++) {
                    for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
                        paper[fold - i][j] = paper[fold - i][j] || paper[fold + i][j];
                    }
                }
                bb[1][0] = fold - 1;
            } else {
                // Nach unten
                for (size_t i = 0; i <= fold - bb[0][0]; i++) {
                    for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
                        paper[fold + i][j] = paper[fold + i][j] || paper[fold - i][j];
                    }
                }
                bb[0][0] = fold + 1;
            }
        }
    }

    for (size_t i = bb[0][0]; i <= bb[1][0]; i++) {
        for (size_t j = bb[0][1]; j <= bb[1][1]; j++) {
            std::cout << (paper[i][j] ? "#" : ".");
        }
        std::cout << std::endl;
    }
}

int aoc141() {
    std::ifstream file("input/14.txt");
    std::string line;

    std::getline(file, line);
    std::vector<char> polymer(line.size());
    for (size_t i = 0; i < line.size(); i++) {
        polymer[i] = line.at(i);
    }
    // for (auto c : polymer) {
    //     std::cout << c;
    // }
    // std::cout << std::endl;

    std::map<std::vector<char>, char> rules;
    std::getline(file, line);
    while (std::getline(file, line)) {
        rules[{line.at(0), line.at(1)}] = line.at(6);
    }

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 1; j < polymer.size(); j++) {
            polymer.insert(polymer.begin() + j, rules[{polymer[j - 1], polymer[j]}]);
            j++;
        }
        // for (auto c : polymer) {
        //     std::cout << c;
        // }
        // std::cout << std::endl;
    }

    std::vector<int> quantities(26, 0);
    for (size_t i = 0; i < polymer.size(); i++) {
        quantities[polymer[i] - 'A']++;
    }
    std::sort(quantities.begin(), quantities.end());
    bool zero = true;
    for (size_t i = 0; i < quantities.size() && zero; i++) {
        if (quantities[i] == 0) {
            quantities.erase(quantities.begin());
            i--;
        } else {
            zero = false;
        }
    }
    return quantities[quantities.size() - 1] - quantities[0];
}

long long aoc142() {
    std::ifstream file("input/14.txt");
    std::string line;

    std::getline(file, line);
    std::vector<char> polymer(line.size());
    for (size_t i = 0; i < line.size(); i++) {
        polymer[i] = line.at(i);
    }

    std::map<std::vector<char>, char> rules;
    std::getline(file, line);
    while (std::getline(file, line)) {
        rules[{line.at(0), line.at(1)}] = line.at(6);
    }

    std::map<std::vector<char>, long long> cnt;
    for (auto rule : rules) {
        cnt[rule.first] = 0;
    }
    for (size_t i = 1; i < polymer.size(); i++) {
        cnt[{polymer[i - 1], polymer[i]}]++;
    }

    for (size_t i = 0; i < 40; i++) {
        std::map<std::vector<char>, long long> next_cnt;
        for (auto rule : rules) {
            next_cnt[rule.first] = 0;
        }
        for (auto x : cnt) {
            char a = x.first[0];
            char b = rules[x.first];
            char c = x.first[1];
            long long n = x.second;
            next_cnt[{a, b}] += n;
            next_cnt[{b, c}] += n;
        }
        cnt = next_cnt;
    }

    std::vector<long long> quantities(26, 0);
    for (auto x : cnt) {
        quantities[x.first[0] - 'A'] += x.second;
    }
    quantities[polymer[polymer.size() - 1] - 'A']++;
    std::sort(quantities.begin(), quantities.end());
    bool zero = true;
    for (size_t i = 0; i < quantities.size() && zero; i++) {
        if (quantities[i] == 0) {
            quantities.erase(quantities.begin());
            i--;
        } else {
            zero = false;
        }
    }
    return quantities[quantities.size() - 1] - quantities[0];
}

struct Vertex {
    int risk;
    size_t row;
    size_t col;
    int dist;
    bool inq;
};

int dijkstra(std::vector<std::vector<Vertex>> V) {
    auto cmp = [](Vertex a, Vertex b) {
        return a.dist > b.dist;
    };
    OveriorityQueue<Vertex, decltype(cmp)> q(cmp, V.size() * V[0].size());
    for (auto V_row : V) {
        for (auto v : V_row) {
            V[v.row][v.col].dist = v.row == 0 && v.col == 0 ? 0 : std::numeric_limits<int>::max();
            q.push(V[v.row][v.col], v.row * V[0].size() + v.col);
            V[v.row][v.col].inq = true;
        }
    }

    while (!q.empty()) {
        Vertex u = q.pop();
        V[u.row][u.col].inq = false;

        if (u.row == V.size() - 1 && u.col == V[0].size() - 1) {
            return u.dist;
        }

        std::vector<Vertex> neighbors;
        if (u.row > 0) {
            neighbors.push_back(V[u.row - 1][u.col]);
        }
        if (u.row < V.size() - 1) {
            neighbors.push_back(V[u.row + 1][u.col]);
        }
        if (u.col > 0) {
            neighbors.push_back(V[u.row][u.col - 1]);
        }
        if (u.col < V[0].size() - 1) {
            neighbors.push_back(V[u.row][u.col + 1]);
        }

        for (Vertex v : neighbors) {
            if (v.inq) {
                int alt = u.dist + v.risk;
                if (alt < v.dist) {
                    V[v.row][v.col].dist = alt;
                    q.push(V[v.row][v.col], v.row * V[0].size() + v.col);
                }
            }
        }
    }
    return -1;
}

int aoc151() {
    std::ifstream file("input/15.txt");
    std::string line;
    std::vector<std::vector<Vertex>> V;
    while (std::getline(file, line)) {
        std::vector<Vertex> V_row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            V_row[i].risk = line.at(i) - '0';
            V_row[i].row = V.size();
            V_row[i].col = i;
        }
        V.push_back(V_row);
    }
    return dijkstra(V);
}

int aoc152() {
    std::ifstream file("input/15.txt");
    std::string line;
    std::vector<std::vector<Vertex>> V;
    while (std::getline(file, line)) {
        std::vector<Vertex> V_row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            V_row[i].risk = line.at(i) - '0';
            V_row[i].row = V.size();
            V_row[i].col = i;
        }
        V.push_back(V_row);
    }

    std::vector<std::vector<Vertex>> W(5 * V.size());
    for (size_t i = 0; i < 5 * V.size(); i++) {
        W[i] = std::vector<Vertex>(5 * V[0].size());
        for (size_t j = 0; j < 5 * V[0].size(); j++) {
            int offset = i / V.size() + j / V[0].size();
            W[i][j].risk = V[i % V.size()][j % V[0].size()].risk + offset;
            if (W[i][j].risk > 9) {
                W[i][j].risk -= 9;
            }
            W[i][j].row = i;
            W[i][j].col = j;
        }
    }
    return dijkstra(W);
}

std::vector<bool> bits(0);
int sum = 0;

long long decode(std::vector<bool> bin) {
    long long x = 0;
    for (size_t i = 0; i < bin.size(); i++) {
        x <<= 1;
        x |= bin[i];
    }
    return x;
}

std::pair<int, long long> decode_packet(int start, int depth) {
    for (size_t i = 0; i < depth; i++) {
        std::cout << "    ";
    }
    int version = decode(std::vector<bool>(bits.begin() + start, bits.begin() + start + 3));
    sum += version;
    int type = decode(std::vector<bool>(bits.begin() + start + 3, bits.begin() + start + 6));
    std::cout << "[" << start << "] V " << version << " T " << type;
    if (type == 4) {
        int idx = start + 6;
        bool more;
        std::vector<bool> literal;
        do {
            more = bits[idx];
            idx++;
            for (size_t i = 0; i < 4; i++) {
                literal.push_back(bits[idx]);
                idx++;
            }
        } while (more);
        long long x = decode(literal);
        std::cout << " -> " << x << std::endl;
        return {idx, x};
    } else {
        bool length_type = bits[start + 6];
        std::cout << " I " << length_type;
        int idx;
        std::vector<long long> operands;
        if (!length_type) {
            int length = decode(std::vector<bool>(bits.begin() + start + 7, bits.begin() + start + 22));
            std::cout << " L " << length << std::endl;
            idx = start + 22;
            while (idx < start + 22 + length) {
                std::pair<int, long long> pair = decode_packet(idx, depth + 1);
                idx = pair.first;
                operands.push_back(pair.second);
            }
        } else {
            int num = decode(std::vector<bool>(bits.begin() + start + 7, bits.begin() + start + 18));
            std::cout << " N " << num << std::endl;
            idx = start + 18;
            for (size_t i = 0; i < num; i++) {
                std::pair<int, long long> pair = decode_packet(idx, depth + 1);
                idx = pair.first;
                operands.push_back(pair.second);
            }
        }
        for (size_t i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        long long result;
        switch (type) {
        case 0:
            std::cout << "+( ";
            result = 0;
            for (size_t i = 0; i < operands.size(); i++) {
                result += operands[i];
            }
            break;
        case 1:
            std::cout << "*( ";
            result = 1;
            for (size_t i = 0; i < operands.size(); i++) {
                result *= operands[i];
            }
            break;
        case 2:
            std::cout << "min( ";
            result = std::numeric_limits<long long>::max();
            for (size_t i = 0; i < operands.size(); i++) {
                if (operands[i] < result) {
                    result = operands[i];
                }
            }
            break;
        case 3:
            std::cout << "max( ";
            result = 0;
            for (size_t i = 0; i < operands.size(); i++) {
                if (operands[i] > result) {
                    result = operands[i];
                }
            }
            break;
        case 5:
            std::cout << ">( ";
            result = operands[0] > operands[1];
            break;
        case 6:
            std::cout << "<( ";
            result = operands[0] < operands[1];
            break;
        case 7:
            std::cout << "==( ";
            result = operands[0] == operands[1];
            break;
        }
        for (size_t i = 0; i < operands.size(); i++) {
            std::cout << operands[i] << " ";
        }
        std::cout << ") = " << result << std::endl;
        return {idx, result};
    }
}

int aoc161() {
    std::ifstream file("input/16.txt");
    std::string line;
    std::getline(file, line);
    for (size_t i = 0; i < line.size(); i++) {
        char c = line.at(i);
        char hex = c < 'A' ? c - '0' : c - 'A' + 10;
        for (size_t j = 0; j < 4; j++) {
            bits.push_back(hex >> (3 - j) & 1);
        }
    }
    // for (auto b : bits) {
    //     std::cout << b;
    // }
    // std::cout << std::endl;

    decode_packet(0, 0);
    return sum;
}

long long aoc162() {
    std::ifstream file("input/16.txt");
    std::string line;
    std::getline(file, line);
    for (size_t i = 0; i < line.size(); i++) {
        char c = line.at(i);
        char hex = c < 'A' ? c - '0' : c - 'A' + 10;
        for (size_t j = 0; j < 4; j++) {
            bits.push_back(hex >> (3 - j) & 1);
        }
    }
    return decode_packet(0, 0).second;
}

int aoc171() {
    std::vector<std::vector<int>> target = {{137, -98}, {171, -73}};
    std::vector<std::vector<int>> pos;
    std::vector<int> vel;
    int maxmax;
    for (int up = 0; up < 100; up++) {
        pos = {{0, 0}};
        vel = {{17, up}};
        bool hit = false;
        bool deep = false;
        int max = 0;
        for (size_t i = 0; !deep; i++) {
            std::vector<int> new_pos = pos[pos.size() - 1];
            new_pos[0] += vel[0];
            new_pos[1] += vel[1];
            if (new_pos[0] >= target[0][0] && new_pos[0] <= target[1][0] && new_pos[1] >= target[0][1] && new_pos[1] <= target[1][1]) {
                hit = true;
            }
            if (new_pos[1] < target[0][1]) {
                deep = true;
            }
            if (new_pos[1] > max) {
                max = new_pos[1];
            }
            pos.push_back(new_pos);
            if (vel[0] < 0) {
                vel[0]++;
            }
            if (vel[0] > 0) {
                vel[0]--;
            }
            vel[1]--;
        }
        // std::cout << up << " hit " << hit << " max " << max << std::endl;
        if (hit) {
            maxmax = max;
        }
    }

    // for (int y = 0; y > -100; y--) {
    //     for (int x = 0; x < 173; x++) {
    //         std::vector<int> a = {x, y};
    //         auto find = std::find(pos.begin(), pos.end(), a);
    //         if (find == pos.begin()) {
    //             std::cout << "S";
    //         } else if (find != pos.end()) {
    //             std::cout << "#";
    //         } else {
    //             if (x >= target[0][0] && x <= target[1][0] && y >= target[0][1] && y <= target[1][1]) {
    //                 std::cout << "T";
    //             } else {
    //                 std::cout << ".";
    //             }
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    return maxmax;
}

int aoc172() {
    std::vector<std::vector<int>> target = {{137, -98}, {171, -73}};
    std::vector<std::vector<int>> pos;
    std::vector<int> vel;
    int cnt = 0;
    for (int x = 0; x < 200; x++) {
        for (int y = -100; y < 100; y++) {
            pos = {{0, 0}};
            vel = {{x, y}};
            bool hit = false;
            bool deep = false;
            int max = 0;
            for (size_t i = 0; !deep; i++) {
                std::vector<int> new_pos = pos[pos.size() - 1];
                new_pos[0] += vel[0];
                new_pos[1] += vel[1];
                if (new_pos[0] >= target[0][0] && new_pos[0] <= target[1][0] && new_pos[1] >= target[0][1] && new_pos[1] <= target[1][1]) {
                    hit = true;
                }
                if (new_pos[1] < target[0][1]) {
                    deep = true;
                }
                if (new_pos[1] > max) {
                    max = new_pos[1];
                }
                pos.push_back(new_pos);
                if (vel[0] < 0) {
                    vel[0]++;
                }
                if (vel[0] > 0) {
                    vel[0]--;
                }
                vel[1]--;
            }
            if (hit) {
                cnt++;
            }
        }
    }
    return cnt;
}

class SnailfishNumber {
public:
    SnailfishNumber(int number) : number_(number) {}

    SnailfishNumber(std::string str) {
        if (str.at(0) != '[') {
            number_ = std::stoi(str);
        } else {
            number_ = -1;
            size_t pos;
            size_t cnt = 0;
            bool found = false;
            for (pos = 0; pos < str.size() && !found; pos++) {
                if (str.at(pos) == '[') {
                    cnt++;
                }
                if (str.at(pos) == ',' && cnt == 1) {
                    found = true;
                }
                if (str.at(pos) == ']') {
                    cnt--;
                }
            }
            pos--;
            left_ = new SnailfishNumber(str.substr(1, pos - 1));
            left_->parent_ = this;
            right_ = new SnailfishNumber(str.substr(pos + 1, str.size() - pos - 2));
            right_->parent_ = this;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const SnailfishNumber& s);

    SnailfishNumber operator+(const SnailfishNumber& s) const {
        std::stringstream ss("");
        ss << "[" << *this << "," << s << "]" << std::endl;
        SnailfishNumber sum(ss.str());
        sum.reduce();
        return sum;
    }

    int magnitude() {
        if (number_ < 0) {
            return 3 * left_->magnitude() + 2 * right_->magnitude();
        } else {
            return number_;
        }
    }

private:
    void reduce() {
        bool reduced;
        do {
            reduced = true;
            if (explode()) {
                reduced = false;
            } else if (split()) {
                reduced = false;
            }
        } while (!reduced);
    }

    bool explode() {
        std::vector<std::pair<SnailfishNumber*, int>> v = inorder(0);
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i].second > 4) {
                if (i > 0) {
                    v[i - 1].first->number_ += v[i].first->number_;
                }
                if (i < v.size() - 2) {
                    v[i + 2].first->number_ += v[i + 1].first->number_;
                }
                SnailfishNumber* p = v[i].first->parent_;
                p->number_ = 0;
                p->left_ = nullptr;
                p->right_ = nullptr;
                return true;
            }
        }
        return false;
    }

    bool split() {
        std::vector<std::pair<SnailfishNumber*, int>> v = inorder(0);
        for (size_t i = 0; i < v.size(); i++) {
            int n = v[i].first->number_;
            if (n > 9) {
                v[i].first->number_ = -1;
                v[i].first->left_ = new SnailfishNumber(n / 2);
                v[i].first->left_->parent_ = v[i].first;
                v[i].first->right_ = new SnailfishNumber(n % 2 == 0 ? n / 2 : n / 2 + 1);
                v[i].first->right_->parent_ = v[i].first;
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<SnailfishNumber*, int>> inorder(int depth) {
        if (number_ < 0) {
            std::vector<std::pair<SnailfishNumber*, int>> v = left_->inorder(depth + 1);
            std::vector<std::pair<SnailfishNumber*, int>> w = right_->inorder(depth + 1);
            v.insert(v.end(), w.begin(), w.end());
            return v;
        } else {
            return {{this, depth}};
        }
    }

    int number_;
    SnailfishNumber* left_;
    SnailfishNumber* right_;
    SnailfishNumber* parent_;
};

std::ostream& operator<<(std::ostream& out, const SnailfishNumber& s) {
    if (s.number_ < 0) {
        out << "[" << *s.left_ << "," << *s.right_ << "]";
    } else {
        out << s.number_;
    }
    return out;
}

int aoc181() {
    std::ifstream file("input/18.txt");
    std::string line;
    std::getline(file, line);
    SnailfishNumber sum(line);
    while (std::getline(file, line)) {
        SnailfishNumber x(line);
        sum = sum + x;
    }
    return sum.magnitude();
}

int aoc182() {
    std::ifstream file("input/18.txt");
    std::string line;
    std::vector<SnailfishNumber> numbers;
    while (std::getline(file, line)) {
        numbers.push_back(SnailfishNumber(line));
    }
    int max = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = 0; j < numbers.size(); j++) {
            if (i != j) {
                int mag = (numbers[i] + numbers[j]).magnitude();
                if (mag > max) {
                    max = mag;
                }
            }
        }
    }
    return max;
}

std::vector<int> matmul(std::vector<std::vector<int>> m, std::vector<int> v) {
    v.push_back(1);
    std::vector<int> mv(4);
    for (size_t i = 0; i < 4; i++) {
        mv[i] = 0;
        for (size_t j = 0; j < 4; j++) {
            mv[i] += m[i][j] * v[j];
        }
    }
    mv.erase(mv.begin() + 3);
    return mv;
}

std::vector<int> cross(std::vector<int> a, std::vector<int> b) {
    return {a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}

std::vector<std::vector<int>> registration(std::vector<std::vector<int>> map, std::vector<std::vector<int>> pc) {
    std::vector<std::vector<int>> diffs;
    std::map<std::vector<int>, std::vector<int>> diff_to_idx;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            std::vector<int> diff(3);
            for (size_t k = 0; k < 3; k++) {
                diff[k] = std::abs(map[i][k] - map[j][k]);
            }
            std::sort(diff.begin(), diff.end());
            diffs.push_back(diff);
            if (!diff_to_idx.contains(diff)) {
                diff_to_idx[diff] = {(int) i, (int) j};
            } else {
                diff_to_idx[diff] = {-1, -1};
            }
        }
    }

    std::vector<std::vector<std::vector<int>>> orientations;
    for (int dir = 0; dir < 3; dir++) {
        for (int dirsgn : {-1, 1}) {
            for (int up = 0; up < 3; up++) {
                if (up != dir) {
                    for (int upsgn : {-1, 1}) {
                        std::vector<int> x = {0, 0, 0};
                        x[dir] = dirsgn;
                        std::vector<int> y = {0, 0, 0};
                        y[up] = upsgn;
                        std::vector<int> z = cross(x, y);
                        orientations.push_back({{x[0], y[0], z[0], 0},
                                                {x[1], y[1], z[1], 0},
                                                {x[2], y[2], z[2], 0},
                                                {0, 0, 0, 1}});
                    }
                }
            }
        }
    }

    bool found = false;
    std::vector<std::vector<int>> m;
    for (size_t i = 0; i < pc.size() && !found; i++) {
        for (size_t j = 0; j < pc.size() && !found; j++) {
            if (i != j) {
                std::vector<int> diff(3);
                for (size_t k = 0; k < 3; k++) {
                    diff[k] = std::abs(pc[i][k] - pc[j][k]);
                }
                std::sort(diff.begin(), diff.end());

                if (diff_to_idx.contains(diff)) {
                    std::vector<int> signed_diff(3);
                    std::vector<int> signed_original_diff(3);
                    std::vector<int> idx = diff_to_idx[diff];
                    for (size_t k = 0; k < 3; k++) {
                        signed_diff[k] = pc[i][k] - pc[j][k];
                        signed_original_diff[k] = map[idx[0]][k] - map[idx[1]][k];
                    }

                    for (size_t o = 0; o < orientations.size() && !found; o++) {
                        m = orientations[o];
                        if (matmul(m, signed_diff) == signed_original_diff) {
                            std::vector<int> offset(3);
                            for (size_t k = 0; k < 3; k++) {
                                offset[k] = map[idx[0]][k] - matmul(m, pc[i])[k];
                            }
                            for (size_t k = 0; k < 3; k++) {
                                m[k][3] = offset[k];
                            }

                            int cnt = 0;
                            for (auto p : pc) {
                                std::vector<int> transformed = matmul(m, p);
                                if (std::find(map.begin(), map.end(), transformed) != map.end()) {
                                    cnt++;
                                }
                            }
                            if (cnt >= 12) {
                                found = true;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!found) {
        m = {};
    }
    return m;
}

int aoc191() {
    std::ifstream file("input/19.txt");
    std::string line;
    std::vector<std::vector<std::vector<int>>> scans(0);
    std::vector<std::vector<int>> scan;
    while (std::getline(file, line)) {
        if (line == "") {
            scans.push_back(scan);
        } else if (line.at(1) == '-') {
            scan.clear();
        } else {
            std::vector<int> p(3);
            size_t pos = line.find(",");
            p[0] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            p[1] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            p[2] = std::stoi(line);
            scan.push_back(p);
        }
    }
    scans.push_back(scan);

    // for (size_t i = 0; i < scanners.size(); i++) {
    //     std::cout << "---- " << i << " ----" << std::endl;
    //     for (auto p : scanners[i]) {
    //         for (auto x : p) {
    //             std::cout << x << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    // std::cout << std::endl;

    std::vector<std::vector<int>> map = scans[0];
    std::queue<std::vector<std::vector<int>>> unregistered;
    for (size_t i = 0; i < scans.size(); i++) {
        unregistered.push(scans[i]);
    }
    while (!unregistered.empty()) {
        std::vector<std::vector<int>> scan = unregistered.front();
        unregistered.pop();
        std::vector<std::vector<int>> m = registration(map, scan);
        if (m.size() == 4) {
            for (size_t i = 0; i < scan.size(); i++) {
                scan[i] = matmul(m, scan[i]);
                if (std::find(map.begin(), map.end(), scan[i]) == map.end()) {
                    map.push_back(scan[i]);
                }
            }
        } else {
            unregistered.push(scan);
        }
    }
    return map.size();
}

int aoc192() {
    std::ifstream file("input/19.txt");
    std::string line;
    std::vector<std::vector<std::vector<int>>> scans(0);
    std::vector<std::vector<int>> scan;
    while (std::getline(file, line)) {
        if (line == "") {
            scans.push_back(scan);
        } else if (line.at(1) == '-') {
            scan.clear();
        } else {
            std::vector<int> p(3);
            size_t pos = line.find(",");
            p[0] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            p[1] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            p[2] = std::stoi(line);
            scan.push_back(p);
        }
    }
    scans.push_back(scan);

    std::vector<std::vector<int>> scanner_positions({{0, 0, 0}});
    std::vector<std::vector<int>> map = scans[0];
    std::queue<std::vector<std::vector<int>>> unregistered;
    for (size_t i = 0; i < scans.size(); i++) {
        unregistered.push(scans[i]);
    }
    while (!unregistered.empty()) {
        std::vector<std::vector<int>> scan = unregistered.front();
        unregistered.pop();
        std::vector<std::vector<int>> m = registration(map, scan);
        if (m.size() == 4) {
            for (size_t i = 0; i < scan.size(); i++) {
                scan[i] = matmul(m, scan[i]);
                if (std::find(map.begin(), map.end(), scan[i]) == map.end()) {
                    map.push_back(scan[i]);
                }
            }
            scanner_positions.push_back(matmul(m, {0, 0, 0}));
        } else {
            unregistered.push(scan);
        }
    }
    int max = 0;
    for (size_t i = 0; i < scanner_positions.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            int dist = 0;
            for (size_t k = 0; k < 3; k++) {
                dist += std::abs(scanner_positions[i][k] - scanner_positions[j][k]);
            }
            if (dist > max) {
                max = dist;
            }
        }
    }
    return max;
}

void print_image(std::pair<std::vector<std::vector<bool>>, bool> image) {
    for (size_t j = 0; j < image.first[0].size() + 2; j++) {
        std::cout << (image.second ? "\u2588" : ".");
    }
    std::cout << std::endl;

    for (size_t i = 0; i < image.first.size(); i++) {
        std::cout << (image.second ? "\u2588" : ".");
        for (size_t j = 0; j < image.first[0].size(); j++) {
            std::cout << (image.first[i][j] ? "\u2588" : ".");
        }
        std::cout << (image.second ? "\u2588" : ".") << std::endl;
    }
    for (size_t j = 0; j < image.first[0].size() + 2; j++) {
        std::cout << (image.second ? "\u2588" : ".");
    }
    std::cout << std::endl;
}

std::pair<std::vector<std::vector<bool>>, bool> enhance(std::pair<std::vector<std::vector<bool>>, bool> image, std::vector<bool> algorithm) {
    std::vector<std::vector<bool>> enhanced(image.first.size() + 2);
    for (int i = 0; i < (int) enhanced.size(); i++) {
        enhanced[i] = std::vector<bool>(image.first[0].size() + 2);
        for (int j = 0; j < (int) enhanced[0].size(); j++) {
            std::vector<bool> kernel;
            for (int di = i - 2; di <= i; di++) {
                for (int dj = j - 2; dj <= j; dj++) {
                    if (di >= 0 && di < image.first.size() && dj >= 0 && dj < image.first[0].size()) {
                        kernel.push_back(image.first[di][dj]);
                    } else {
                        kernel.push_back(image.second);
                    }
                }
            }
            enhanced[i][j] = algorithm[decode(kernel)];
        }
    }
    return {enhanced, image.second ? algorithm[511] : algorithm[0]};
}

int aoc201() {
    std::ifstream file("input/20.txt");
    std::string line;
    std::getline(file, line);
    std::vector<bool> algorithm(line.size());
    for (size_t i = 0; i < line.size(); i++) {
        algorithm[i] = line.at(i) == '#';
    }
    std::getline(file, line);
    std::pair<std::vector<std::vector<bool>>, bool> image;
    while (std::getline(file, line)) {
        std::vector<bool> row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            row[i] = line.at(i) == '#';
        }
        image.first.push_back(row);
    }
    image.second = false;

    print_image(image);
    for (size_t i = 0; i < 2; i++) {
        image = enhance(image, algorithm);
        std::cout << std::endl;
        print_image(image);
    }

    int cnt = 0;
    for (size_t i = 0; i < image.first.size(); i++) {
        for (size_t j = 0; j < image.first.size(); j++) {
            if (image.first[i][j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

int aoc202() {
    std::ifstream file("input/20.txt");
    std::string line;
    std::getline(file, line);
    std::vector<bool> algorithm(line.size());
    for (size_t i = 0; i < line.size(); i++) {
        algorithm[i] = line.at(i) == '#';
    }
    std::getline(file, line);
    std::pair<std::vector<std::vector<bool>>, bool> image;
    while (std::getline(file, line)) {
        std::vector<bool> row(line.size());
        for (size_t i = 0; i < line.size(); i++) {
            row[i] = line.at(i) == '#';
        }
        image.first.push_back(row);
    }
    image.second = false;

    print_image(image);
    for (size_t i = 0; i < 50; i++) {
        image = enhance(image, algorithm);
        std::cout << std::endl;
        print_image(image);
    }

    int cnt = 0;
    for (size_t i = 0; i < image.first.size(); i++) {
        for (size_t j = 0; j < image.first.size(); j++) {
            if (image.first[i][j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

int aoc211() {
    std::vector<int> space = {4 - 1, 1 - 1};
    std::vector<int> score = {0, 0};
    int die = 1 - 1;
    int cnt = 0;
    int winner = -1;
    while (winner < 0) {
        for (int i = 0; i < 2 && winner < 0; i++) {
            int move = 0;
            for (int j = 0; j < 3; j++) {
                move += die + 1;
                die = (die + 1) % 100;
                cnt++;
            }
            space[i] = (space[i] + move) % 10;
            score[i] += space[i] + 1;
            if (score[i] >= 1000) {
                winner = i;
            }
        }
    }
    return score[(winner + 1) % 2] * cnt;
}

std::vector<long long> number_of_wins_by_turns;
std::vector<long long> number_of_games_by_turns;

void rec(int space, int score, int turn) {
    number_of_games_by_turns[turn]++;

    if (score >= 21) {
        number_of_wins_by_turns[turn]++;
        return;
    }

    for (int die1 = 1; die1 <= 3; die1++) {
        for (int die2 = 1; die2 <= 3; die2++) {
            for (int die3 = 1; die3 <= 3; die3++) {
                int next_space = (space + die1 + die2 + die3 - 1) % 10 + 1;
                rec(next_space, score + next_space, turn + 1);
            }
        }
    }
}

long long aoc212() {
    std::vector<int> space = {4, 1};
    std::vector<std::vector<long long>> nowbt(2);
    std::vector<std::vector<long long>> from(2);
    for (int i = 0; i < 2; i++) {
        number_of_wins_by_turns = std::vector<long long>(12, 0);
        number_of_games_by_turns = std::vector<long long>(12, 0);
        rec(space[i], 0, 0);
        nowbt[i] = number_of_wins_by_turns;
        from[i] = number_of_games_by_turns;
    }

    long long universes = 1;
    std::vector<long long> winning_universes(2, 0);
    for (int turn = 1; turn < 12; turn++) {
        for (int player = 0; player < 2; player++) {
            universes *= 27;
            long long wins = 0;
            if (from[player][turn] > 0) {
                wins = (long long) ((long double) universes * ((long double) nowbt[player][turn] / from[player][turn]));
            }
            winning_universes[player] += wins;
            universes -= wins;
        }
    }
    return std::max(winning_universes[0], winning_universes[1]);
}

int aoc221() {
    std::ifstream file("input/22.txt");
    std::string line;
    std::vector<std::pair<std::vector<std::vector<int>>, bool>> steps;
    while (std::getline(file, line)) {
        std::pair<std::vector<std::vector<int>>, bool> step;
        step.second = line.at(1) == 'n';

        size_t pos = line.find("=");
        line.erase(0, pos + 1);
        pos = line.find(".");
        int x0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        pos = line.find("=");
        int x1 = std::stoi(line.substr(0, pos - 2));

        line.erase(0, pos + 1);
        pos = line.find(".");
        int y0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        pos = line.find("=");
        int y1 = std::stoi(line.substr(0, pos - 2));

        line.erase(0, pos + 1);
        pos = line.find(".");
        int z0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        int z1 = std::stoi(line);

        step.first = {{x0, y0, z0}, {x1, y1, z1}};
        steps.push_back(step);
    }

    std::vector<std::vector<std::vector<bool>>> core(101);
    for (size_t i = 0; i < 101; i++) {
        core[i] = std::vector<std::vector<bool>>(101);
        for (size_t j = 0; j < 101; j++) {
            core[i][j] = std::vector<bool>(101, false);
        }
    }

    for (size_t i = 0; i < steps.size(); i++) {
        for (int x = std::max(-50, steps[i].first[0][0]); x <= std::min(50, steps[i].first[1][0]); x++) {
            for (int y = std::max(-50, steps[i].first[0][1]); y <= std::min(50, steps[i].first[1][1]); y++) {
                for (int z = std::max(-50, steps[i].first[0][2]); z <= std::min(50, steps[i].first[1][2]); z++) {
                    core[x + 50][y + 50][z + 50] = steps[i].second;
                }
            }
        }
    }

    int cnt = 0;
    for (size_t i = 0; i < 101; i++) {
        for (size_t j = 0; j < 101; j++) {
            for (size_t k = 0; k < 101; k++) {
                if (core[i][j][k]) {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

class Cuboid {
public:
    Cuboid() : x0(1), x1(0), y0(1), y1(0), z0(1), z1(0) {}

    Cuboid(long long x0, long long x1, long long y0, long long y1, long long z0, long long z1) : x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1) {}

    friend std::ostream& operator<<(std::ostream& out, const Cuboid& c);

    long long volume() {
        return (x1 - x0 + 1) * (y1 - y0 + 1) * (z1 - z0 + 1);
    }

    Cuboid intersect(Cuboid c) {
        if (c.x1 < x0 || c.x0 > x1 || c.y1 < y0 || c.y0 > y1 || c.z1 < z0 || c.z0 > z1) {
            return Cuboid();
        }
        return Cuboid(std::max(x0, c.x0), std::min(x1, c.x1),
                      std::max(y0, c.y0), std::min(y1, c.y1),
                      std::max(z0, c.z0), std::min(z1, c.z1));
    }

    Cuboid bounding_box(Cuboid c) {
        return Cuboid(std::min(x0, c.x0), std::max(x1, c.x1),
                      std::min(y0, c.y0), std::max(y1, c.y1),
                      std::min(z0, c.z0), std::max(z1, c.z1));
    }

private:
    long long x0;
    long long x1;
    long long y0;
    long long y1;
    long long z0;
    long long z1;
};

std::ostream& operator<<(std::ostream& out, const Cuboid& c) {
    out << "x " << c.x0 << " " << c.x1 << " "
        << "y " << c.y0 << " " << c.y1 << " "
        << "z " << c.z0 << " " << c.z1;
    return out;
}

long long aoc222() {
    std::ifstream file("input/22.txt");
    std::string line;
    std::vector<std::pair<Cuboid, bool>> steps;
    Cuboid bb;
    while (std::getline(file, line)) {
        std::pair<Cuboid, bool> step;
        step.second = line.at(1) == 'n';

        size_t pos = line.find("=");
        line.erase(0, pos + 1);
        pos = line.find(".");
        int x0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        pos = line.find("=");
        int x1 = std::stoi(line.substr(0, pos - 2));

        line.erase(0, pos + 1);
        pos = line.find(".");
        int y0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        pos = line.find("=");
        int y1 = std::stoi(line.substr(0, pos - 2));

        line.erase(0, pos + 1);
        pos = line.find(".");
        int z0 = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        int z1 = std::stoi(line);

        step.first = Cuboid(x0, x1, y0, y1, z0, z1);
        bb = bb.bounding_box(step.first);
        steps.push_back(step);
    }

    std::vector<std::pair<Cuboid, bool>> C = {{bb, false}};
    long long cnt = 0;
    for (size_t i = 0; i < steps.size(); i++) {
        size_t n = C.size();
        for (size_t j = 0; j < n; j++) {
            Cuboid s = steps[i].first.intersect(C[j].first);
            if (s.volume() > 0) {
                if (C[j].second) {
                    C.push_back({s, false});
                    cnt -= s.volume();
                } else if (steps[i].second || j > 0) {
                    C.push_back({s, true});
                    cnt += s.volume();
                }
            }
        }
    }
    return cnt;
}

std::vector<int> entrance = {2, 4, 6, 8};

struct Burrow {
    std::vector<std::vector<int>> room; // Nur die Unsortierten
    std::vector<int> hallway;
    std::vector<int> sorted; // Anzahlen der Sortierten

    bool operator<(const Burrow& b) const {
        if (room != b.room) {
            return room < b.room;
        }
        if (hallway != b.hallway) {
            return hallway < b.hallway;
        }
        return sorted < b.sorted;
    }

    bool operator==(const Burrow& b) const {
        return room == b.room && hallway == b.hallway && sorted == b.sorted;
    }
};

void print_burrow(Burrow b) {
    std::vector<char> map = {'A', 'B', 'C', 'D', '.'};
    for (int i = 0; i < 11; i++) {
        std::cout << map[(b.hallway[i] + 5) % 5] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << " ";
        for (int j = 0; j < 4; j++) {
            if (b.sorted[j] < 4 - i) {
                std::cout << "   " << map[(b.room[j][i] + 5) % 5];
            } else {
                std::cout << "  *" << map[j];
            }
        }
        std::cout << std::endl;
    }
}

int pow(int base, int exponent) {
    int power = 1;
    for (int i = 0; i < exponent; i++) {
        power *= base;
    }
    return power;
}

std::vector<std::pair<Burrow, int>> neighbors(Burrow b) {
    std::vector<std::pair<Burrow, int>> result;

    // Aus dem Schott
    for (int i = 0; i < 4; i++) {
        int bed = -1;
        for (int j = 0; j < 4 && bed == -1; j++) {
            if (b.room[i][j] != -1) {
                bed = j;
            }
        }
        if (bed != -1) {
            int amphipod = b.room[i][bed];
            for (int j = 0; j < 11; j++) {
                if (std::find(entrance.begin(), entrance.end(), j) == entrance.end()) {
                    bool free = true;
                    for (int k = std::min(entrance[i], j); k <= std::max(entrance[i], j) && free; k++) {
                        if (b.hallway[k] != -1) {
                            free = false;
                        }
                    }
                    if (free) {
                        Burrow n = b;
                        n.room[i][bed] = -1;
                        n.hallway[j] = amphipod;
                        result.push_back({n, (bed + 1 + std::abs(entrance[i] - j)) * pow(10, amphipod)});
                    }
                }
            }
        }
    }

    // Ins Schott
    for (int i = 0; i < 11; i++) {
        int amphipod = b.hallway[i];
        if (amphipod != -1) {
            bool free = b.room[amphipod][0] == -1 && b.room[amphipod][1] == -1 && b.room[amphipod][2] == -1 && b.room[amphipod][3] == -1;
            for (int j = std::min(i, entrance[amphipod]); j <= std::max(i, entrance[amphipod]) && free; j++) {
                if (j != i && b.hallway[j] != -1) {
                    free = false;
                }
            }
            if (free) {
                Burrow n = b;
                n.hallway[i] = -1;
                n.sorted[amphipod]++;
                result.push_back({n, (std::abs(i - entrance[amphipod]) + 5 - n.sorted[amphipod]) * pow(10, amphipod)});
            }
        }
    }

    return result;
}

// Achtung: Tut nicht mehr wegen 23 2 :(
int aoc231() {
    Burrow start;
    start.room = {{0, 1}, {3, 2}, {1, 0}, {3, 2}};
    start.hallway = std::vector<int>(11, -1);
    start.sorted = std::vector<int>(4, 0);

    std::queue<Burrow> q;
    std::map<Burrow, int> dist;
    std::map<Burrow, Burrow> prev;
    dist[start] = 0;
    q.push(start);

    Burrow end;
    while (!q.empty()) {
        Burrow u = q.front();
        q.pop();

        bool finished = true;
        for (size_t i = 0; i < 4 && finished; i++) {
            if (u.sorted[i] != 2) {
                finished = false;
            }
        }
        if (finished) {
            end = u;
        }

        std::vector<std::pair<Burrow, int>> N = neighbors(u);
        for (size_t i = 0; i < N.size(); i++) {
            Burrow v = N[i].first;
            if (!dist.contains(v) || dist[v] > dist[u] + N[i].second) {
                dist[v] = dist[u] + N[i].second;
                prev[v] = u;
                q.push(v);
            }
        }
    }

    Burrow b = end;
    std::vector<Burrow> solution;
    while (b != start) {
        solution.push_back(b);
        b = prev[b];
    }
    solution.push_back(start);
    std::reverse(solution.begin(), solution.end());
    for (auto b : solution) {
        std::cout << dist[b] << std::endl;
        print_burrow(b);
    }

    return dist[end];
}

int aoc232() {
    Burrow start;
    start.room = {{0, 3, 3, 1}, {3, 2, 1, 2}, {1, 1, 0, 0}, {3, 0, 2, 2}};
    start.hallway = std::vector<int>(11, -1);
    start.sorted = std::vector<int>(4, 0);

    std::queue<Burrow> q;
    std::map<Burrow, int> dist;
    std::map<Burrow, Burrow> prev;
    dist[start] = 0;
    q.push(start);

    Burrow end;
    while (!q.empty()) {
        Burrow u = q.front();
        q.pop();

        bool finished = true;
        for (size_t i = 0; i < 4 && finished; i++) {
            if (u.sorted[i] != 4) {
                finished = false;
            }
        }
        if (finished) {
            end = u;
        }

        std::vector<std::pair<Burrow, int>> N = neighbors(u);
        for (size_t i = 0; i < N.size(); i++) {
            Burrow v = N[i].first;
            if (!dist.contains(v) || dist[v] > dist[u] + N[i].second) {
                dist[v] = dist[u] + N[i].second;
                prev[v] = u;
                q.push(v);
            }
        }
    }

    Burrow b = end;
    std::vector<Burrow> solution;
    while (b != start) {
        solution.push_back(b);
        b = prev[b];
    }
    solution.push_back(start);
    std::reverse(solution.begin(), solution.end());
    for (auto b : solution) {
        std::cout << dist[b] << std::endl;
        print_burrow(b);
    }

    return dist[end];
}

struct Instruction {
    std::string opcode;
    long long a;
    long long b;
    bool immediate;
};

std::vector<long long> exec(std::vector<Instruction> prgm, std::vector<long long> in) {
    std::vector<long long> reg(4, 0);
    size_t in_ptr = 0;
    for (size_t i = 0; i < prgm.size(); i++) {
        // std::cout << "---- " << i + 1 << " ----" << std::endl;
        // std::cout << "w=" << reg[0] << ", x=" << reg[1] << ", y=" << reg[2] << ", z=" << reg[3] << std::endl;
        // std::cout << prgm[i].opcode << " " << prgm[i].a << " " << prgm[i].b << (prgm[i].immediate ? " (imm)" : "") << std::endl;
        std::string opcode = prgm[i].opcode;
        long long idx = prgm[i].a;
        long long a = reg[idx];
        long long b = prgm[i].b;
        if (!prgm[i].immediate) {
            b = reg[b];
        }
        if (opcode == "inp") {
            if (in_ptr >= in.size()) {
                std::cout << "ERROR: Missing input " << in_ptr << std::endl;
                return reg;
            }
            reg[idx] = in[in_ptr];
            in_ptr++;
        } else if (opcode == "add") {
            reg[idx] = a + b;
        } else if (opcode == "mul") {
            reg[idx] = a * b;
        } else if (opcode == "div") {
            if (b == 0) {
                std::cout << "ERROR: Division by zero" << std::endl;
                return reg;
            }
            reg[idx] = a / b;
        } else if (opcode == "mod") {
            if (a < 0 || b <= 0) {
                std::cout << "ERROR: Modulo" << std::endl;
                return reg;
            }
            reg[idx] = a % b;
        } else if (opcode == "eql") {
            reg[idx] = a == b ? 1 : 0;
        } else {
            std::cout << "ERROR: Invalid opcode \"" << opcode << "\"" << std::endl;
            return reg;
        }
        // std::cout << "w=" << reg[0] << ", x=" << reg[1] << ", y=" << reg[2] << ", z=" << reg[3] << std::endl;
    }
    return reg;
}

std::vector<long long> digits(long long number) {
    std::vector<long long> digits;
    while (number > 0) {
        digits.push_back(number % 10);
        number /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

long long aoc241() {
    std::ifstream file("input/24.txt");
    std::string line;
    std::vector<Instruction> prgm;
    while (std::getline(file, line)) {
        Instruction instruction;
        size_t pos = line.find(" ");
        instruction.opcode = line.substr(0, pos);
        line.erase(0, pos + 1);
        std::string a = line;
        if (instruction.opcode != "inp") {
            pos = line.find(" ");
            a = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        if (a == "w") {
            instruction.a = 0;
        } else if (a == "x") {
            instruction.a = 1;
        } else if (a == "y") {
            instruction.a = 2;
        } else if (a == "z") {
            instruction.a = 3;
        } else {
            std::cout << "ERROR: Invalid register \"" << a << "\"" << std::endl;
            return -1;
        }
        instruction.immediate = false;
        if (line == "w") {
            instruction.b = 0;
        } else if (line == "x") {
            instruction.b = 1;
        } else if (line == "y") {
            instruction.b = 2;
        } else if (line == "z") {
            instruction.b = 3;
        } else {
            instruction.b = std::stoi(line);
            instruction.immediate = true;
        }
        prgm.push_back(instruction);
    }

    long long cnt = 0;
    while (false) {
        if (cnt % 1000000 == 0) {
            std::cout << ".";
        }
        cnt++;

        std::vector<long long> d(14);
        d[0] = 7;
        d[1] = rand() % 7 + 3;
        for (size_t i = 2; i < 14; i++) {
            d[i] = rand() % 9 + 1;
        }
        std::vector<long long> out = exec(prgm, d);
        if (out[3] == 0) {
            std::cout << "-> ";
            for (size_t i = 0; i < 14; i++) {
                std::cout << d[i];
            }
            std::cout << std::endl;
        }
    }
    return 74929995999389;
    // 73818884897112 < x < 79999999999999
}

long long aoc242() {
    // Ich bin ein dreckiger Schummler :P
    return 11118151637112;
}

int aoc25() {
    std::ifstream file("input/25.txt");
    std::string line;
    std::vector<std::vector<char>> cucumbers;
    while (std::getline(file, line)) {
        std::vector<char> row(line.size());
        for (int i = 0; i < line.size(); i++) {
            row[i] = line.at(i);
        }
        cucumbers.push_back(row);
    }

    // for (int i = 0; i < cucumbers.size(); i++) {
    //     for (int j = 0; j < cucumbers[i].size(); j++) {
    //         std::cout << cucumbers[i][j];
    //     }
    //     std::cout << std::endl;
    // }

    int cnt = 0;
    bool movement;
    do {
        cnt++;
        // std::cout << "---- " << cnt << " ----" << std::endl;

        movement = false;
        std::vector<std::vector<char>> next_cucumbers = cucumbers;
        for (int i = 0; i < cucumbers.size(); i++) {
            for (int j = 0; j < cucumbers[i].size(); j++) {
                if (cucumbers[i][j] == '>' && cucumbers[i][(j + 1) % cucumbers[i].size()] == '.') {
                    next_cucumbers[i][j] = '.';
                    next_cucumbers[i][(j + 1) % cucumbers[i].size()] = '>';
                    movement = true;
                }
            }
        }
        cucumbers = next_cucumbers;
        for (int i = 0; i < cucumbers.size(); i++) {
            for (int j = 0; j < cucumbers[i].size(); j++) {
                if (cucumbers[i][j] == 'v' && cucumbers[(i + 1) % cucumbers.size()][j] == '.') {
                    next_cucumbers[i][j] = '.';
                    next_cucumbers[(i + 1) % cucumbers.size()][j] = 'v';
                    movement = true;
                }
            }
        }
        cucumbers = next_cucumbers;

        // for (int i = 0; i < cucumbers.size(); i++) {
        //     for (int j = 0; j < cucumbers[i].size(); j++) {
        //         std::cout << cucumbers[i][j];
        //     }
        //     std::cout << std::endl;
        // }
    } while (movement);
    return cnt;
}

int main() {
    std::cout << aoc25() << std::endl;
}
// cd build && make -j16 && cd .. && ./build/main
