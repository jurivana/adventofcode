#pragma once

#include "util.h"

int shortest_path(std::vector<std::vector<int>> map, std::vector<int> start, std::vector<int> target, bool down) {
    int m = map.size();
    int n = map[0].size();
    std::vector<std::vector<bool>> visited(m);
    std::vector<std::vector<int>> dist(m);
    // std::vector<std::vector<std::vector<int>>> prev(m);
    // std::vector<std::vector<bool>> path(m);
    for (int i = 0; i < m; i++) {
        visited[i] = std::vector<bool>(n, false);
        dist[i] = std::vector<int>(n, std::numeric_limits<int>::max());
        // prev[i] = std::vector<std::vector<int>>(n, {-1, -1});
        // path[i] = std::vector<bool>(n, false);
    }
    dist[start[0]][start[1]] = 0;
    while (dist[target[0]][target[1]] == std::numeric_limits<int>::max()) {
        std::vector<int> idx = {-1, -1};
        int min = std::numeric_limits<int>::max();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j] && dist[i][j] < min) {
                    min = dist[i][j];
                    idx = {i, j};
                }
            }
        }
        visited[idx[0]][idx[1]] = true;
        if (down && map[idx[0]][idx[1]] == 0) {
            target = idx;
        }
        int alt = dist[idx[0]][idx[1]] + 1;
        std::vector<std::vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (std::vector<int> dir : dirs) {
            std::vector<int> neighbor_idx = add(idx, dir);
            if (neighbor_idx[0] >= 0 && neighbor_idx[0] < m && neighbor_idx[1] >= 0 && neighbor_idx[1] < n && !visited[neighbor_idx[0]][neighbor_idx[1]]) {
                bool climbing_condition = map[neighbor_idx[0]][neighbor_idx[1]] <= map[idx[0]][idx[1]] + 1;
                if (down) {
                    climbing_condition = map[neighbor_idx[0]][neighbor_idx[1]] >= map[idx[0]][idx[1]] - 1;
                }
                if (climbing_condition && dist[neighbor_idx[0]][neighbor_idx[1]] > alt) {
                    dist[neighbor_idx[0]][neighbor_idx[1]] = alt;
                    // prev[neighbor_idx[0]][neighbor_idx[1]] = idx;
                }
            }
        }
    }
    // std::vector<int> curr = target;
    // while (curr != start) {
    //     path[curr[0]][curr[1]] = true;
    //     curr = prev[curr[0]][curr[1]];
    // }
    // path[start[0]][start[1]] = true;
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (path[i][j]) {
    //             std::cout << ".";
    //         } else {
    //             std::cout << (char) (map[i][j] + 'a');
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    return dist[target[0]][target[1]];
}

void aoc12() {
    std::vector<std::string> input = read("../input/12.txt");
    std::vector<std::vector<int>> map(input.size());
    std::vector<int> start;
    std::vector<int> target;
    for (int i = 0; i < input.size(); i++) {
        map[i] = std::vector<int>(input[i].size());
        for (int j = 0; j < input[i].size(); j++) {
            map[i][j] = input[i].at(j) - 'a';
            if (input[i].at(j) == 'S') {
                map[i][j] = 0;
                start = {i, j};
            }
            if (input[i].at(j) == 'E') {
                map[i][j] = 'z' - 'a';
                target = {i, j};
            }
        }
    }
    std::cout << shortest_path(map, start, target, false) << std::endl;
    std::cout << shortest_path(map, target, start, true) << std::endl;
}
