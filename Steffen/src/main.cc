#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

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

int main() {
    std::cout << aoc052() << std::endl;
}
