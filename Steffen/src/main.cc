#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
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
    return dijkstra(V);
}

int main() {
    std::cout << aoc152() << std::endl;
}
// cd build && make -j16 && cd .. && ./build/main
