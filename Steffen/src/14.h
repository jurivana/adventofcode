#pragma once

#include "util.h"

int fall(std::vector<std::vector<std::vector<int>>> rocks, bool ground) {
    std::vector<int> source = {500, 0};
    std::vector<int> min = source;
    std::vector<int> max = source;
    for (int i = 0; i < rocks.size(); i++) {
        for (int j = 0; j < rocks[i].size(); j++) {
            for (int k = 0; k < 2; k++) {
                if (rocks[i][j][k] < min[k]) {
                    min[k] = rocks[i][j][k];
                }
                if (rocks[i][j][k] > max[k]) {
                    max[k] = rocks[i][j][k];
                }
            }
        }
    }
    if (ground) {
        int height = max[1] - min[1];
        std::vector<std::vector<int>> rock = {{source[0] - height - 3, max[1] + 2},
                                              {source[0] + height + 3, max[1] + 2}};
        rocks.push_back(rock);
        min[0] = rock[0][0];
        max[1] = rock[0][1];
        max[0] = rock[1][0];
    }
    min = sub(min, {1, 1});
    max = add(max, {2, 2});
    std::vector<int> size = sub(max, min);
    std::vector<std::vector<char>> map(size[0]);
    for (int x = 0; x < size[0]; x++) {
        map[x] = std::vector<char>(size[1]);
        for (int y = 0; y < size[1]; y++) {
            map[x][y] = '.';
        }
    }
    std::function<char&(std::vector<int>)> map_access = [min, &map](std::vector<int> index) -> char& {
        index = sub(index, min);
        return map[index[0]][index[1]];
    };
    map_access(source) = '+';
    for (int i = 0; i < rocks.size(); i++) {
        std::vector<int> a = rocks[i][0];
        for (int j = 1; j < rocks[i].size(); j++) {
            std::vector<int> b = rocks[i][j];
            std::vector<int> dir = sub(b, a);
            for (int k = 0; k < 2; k++) {
                if (dir[k] != 0) {
                    dir[k] /= std::abs(dir[k]);
                }
            }
            while (a != b) {
                map_access(a) = '#';
                a = add(a, dir);
            }
            map_access(a) = '#';
        }
    }
    int cnt = 0;
    bool stop = false;
    while (!stop) {
        std::vector<int> sand = source;
        bool rest = false;
        while (!rest) {
            std::vector<int> next = add(sand, {0, 1});
            if (next[1] == max[1]) {
                rest = true;
                stop = true;
            } else {
                if (map_access(next) != '.') {
                    next = add(sand, {-1, 1});
                    if (map_access(next) != '.') {
                        next = add(sand, {1, 1});
                        if (map_access(next) != '.') {
                            map_access(sand) = 'o';
                            rest = true;
                            cnt++;
                            if (sand == source) {
                                stop = true;
                            }
                            break;
                        }
                    }
                }
                sand = next;
            }
        }
    }
    // for (int y = 0; y < size[1]; y++) {
    //     for (int x = 0; x < size[0]; x++) {
    //         std::cout << map[x][y];
    //     }
    //     std::cout << std::endl;
    // }
    return cnt;
}

void aoc14() {
    std::vector<std::string> input = read("../input/14.txt");
    std::vector<std::vector<std::vector<int>>> rocks;
    for (int i = 0; i < input.size(); i++) {
        std::vector<std::vector<int>> rock;
        bool end = false;
        while (!end) {
            int pos = input[i].find(" -> ");
            if (pos == std::string::npos) {
                pos = input[i].size();
                end = true;
            }
            std::string s = input[i].substr(0, pos);
            input[i].erase(0, pos + 4);
            pos = s.find(",");
            std::vector<int> coordinates(2);
            coordinates[0] = std::stoi(s.substr(0, pos));
            coordinates[1] = std::stoi(s.substr(pos + 1, s.size() - pos));
            rock.push_back(coordinates);
        }
        rocks.push_back(rock);
    }
    std::cout << fall(rocks, false) << std::endl;
    std::cout << fall(rocks, true) << std::endl;
}
