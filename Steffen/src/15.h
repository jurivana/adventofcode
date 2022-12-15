#pragma once

#include "util.h"

struct Sensor {
    std::vector<int> position;
    int range;
};

std::vector<int> sensor_x_interval(Sensor sensor, int y) {
    int offset = sensor.range - std::abs(y - sensor.position[1]);
    return {sensor.position[0] - offset, sensor.position[0] + offset};
}

int dummy = -1;
int n_covered(std::vector<Sensor> sensors, std::set<std::vector<int>> beacons, int y,
              int x_start = std::numeric_limits<int>::min(), int x_end = std::numeric_limits<int>::max(),
              bool ignore_devices = false, int& gap_x = dummy) {
    std::map<int, int> changes;
    for (int i = 0; i < sensors.size(); i++) {
        std::vector<int> interval = sensor_x_interval(sensors[i], y);
        if (interval[1] - interval[0] >= 0) {
            if (changes.find(interval[0]) == changes.end()) {
                changes.insert({interval[0], 1});
            } else {
                changes[interval[0]]++;
            }
            if (changes.find(interval[1]) == changes.end()) {
                changes.insert({interval[1], -1});
            } else {
                changes[interval[1]]--;
            }
        }
    }
    int n_covered = 0;
    int n_intervals = 0;
    int last_x = x_start; // Last X-mas
    for (auto [cx, diff] : changes) {
        int x = cx;
        if (n_intervals == 0 && x > x_start) {
            // Begin of covered interval
            if (x - 1 > last_x) {
                gap_x = x - 1;
            }
            last_x = x;
        }
        n_intervals += diff;
        if (n_intervals == 0) {
            // End of covered interval
            if (x > x_end) {
                x = x_end;
            }
            n_covered += x - last_x + 1;
            if (!ignore_devices) {
                std::vector<std::vector<int>> devices;
                for (std::vector<int> beacon : beacons) {
                    devices.push_back(beacon);
                }
                for (int i = 0; i < sensors.size(); i++) {
                    devices.push_back(sensors[i].position);
                }
                for (int i = 0; i < devices.size(); i++) {
                    if (devices[i][1] == y && devices[i][0] >= last_x && devices[i][0] <= x) {
                        n_covered--;
                    }
                }
            }
            last_x = x;
        }
    }
    return n_covered;
}

void aoc15() {
    std::vector<std::string> input = read("../input/15.txt");
    int input_y = 2000000;
    std::vector<Sensor> sensors;
    std::set<std::vector<int>> beacons;
    for (int i = 0; i < input.size(); i++) {
        Sensor sensor;
        sensor.position = std::vector<int>(2);
        input[i].erase(0, 12);
        int pos = input[i].find(",");
        sensor.position[0] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 4);
        pos = input[i].find(":");
        sensor.position[1] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 25);
        pos = input[i].find(",");
        std::vector<int> beacon(2);
        beacon[0] = std::stoi(input[i].substr(0, pos));
        input[i].erase(0, pos + 4);
        beacon[1] = std::stoi(input[i]);
        sensor.range = manhattan(sensor.position, beacon);
        sensors.push_back(sensor);
        beacons.insert(beacon);
    }
    std::cout << n_covered(sensors, beacons, input_y) << std::endl;

    int x;
    int y;
    for (int i = 0; i <= 2 * input_y; i++) {
        y = (i + 3000000) % (2 * input_y); // Cheat ;) but does not take too long without
        x = -1;
        if (n_covered(sensors, beacons, y, 0, 2 * input_y, true, x) < 2 * input_y + 1) {
            break;
        }
    }
    std::cout << (ll) x * 4000000 + y << std::endl;
}
