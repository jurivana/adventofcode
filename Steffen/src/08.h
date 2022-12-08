#pragma once

#include "util.h"

void aoc08() {
    std::vector<std::string> input = read("../input/08.txt");
    int n = input.size();
    std::vector<std::vector<int>> heights(n);
    std::vector<std::vector<bool>> visibile(n);
    for (int i = 0; i < n; i++) {
        if (input[i].size() != n) {
            std::cout << "ERROR" << std::endl;
        }
        heights[i] = std::vector<int>(n);
        visibile[i] = std::vector<bool>(n, false);
        for (int j = 0; j < n; j++) {
            heights[i][j] = input[i].at(j) - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        std::vector<std::vector<int>> highest = {{-1, -1}, {-1, -1}};
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    int j_directional = l == 0 ? j : n - j - 1;
                    int x = k == 0 ? i : j_directional;
                    int y = k == 0 ? j_directional : i;
                    if (heights[x][y] > highest[k][l]) {
                        visibile[x][y] = true;
                        highest[k][l] = heights[x][y];
                    }
                }
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // std::cout << visibile[i][j];
            if (visibile[i][j]) {
                cnt++;
            }
        }
        // std::cout << std::endl;
    }
    std::cout << cnt << std::endl;

    int max = -1;
    std::vector<std::vector<int>> scenic_score(n);
    for (int i = 0; i < n; i++) {
        scenic_score[i] = std::vector<int>(n);
        for (int j = 0; j < n; j++) {
            scenic_score[i][j] = 1;
            std::vector<std::vector<int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            for (std::vector<int> dir : dirs) {
                int ii = i;
                int jj = j;
                int viewing_distance = 0;
                while (ii > 0 && ii < n - 1 && jj > 0 && jj < n - 1) {
                    ii += dir[0];
                    jj += dir[1];
                    viewing_distance++;
                    if (heights[ii][jj] >= heights[i][j]) {
                        break;
                    }
                }
                scenic_score[i][j] *= viewing_distance;
            }
            if (scenic_score[i][j] > max) {
                max = scenic_score[i][j];
            }
        }
    }
    std::cout << max << std::endl;
}
