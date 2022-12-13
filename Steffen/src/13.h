#pragma once

#include "util.h"

struct Packet {
    int number;
    std::vector<Packet> list;
};

std::ostream& operator<<(std::ostream& os, Packet packet) {
    if (packet.number == -1) {
        os << "[";
        if (packet.list.size() > 0) {
            for (int i = 0; i < packet.list.size() - 1; i++) {
                os << packet.list[i] << ",";
            }
            os << packet.list[packet.list.size() - 1];
        }
        os << "]";
    } else {
        os << packet.number;
    }
    return os;
}

Packet read_packet(std::string s) {
    Packet packet;
    if (s.at(0) == '[') {
        packet.number = -1;
        if (s.size() > 2) {
            int depth = 0;
            int last_comma = 0;
            for (int i = 1; i < s.size() - 1; i++) {
                if (s.at(i) == '[') {
                    depth++;
                } else if (s.at(i) == ']') {
                    depth--;
                }
                if (depth == 0) {
                    if (s.at(i) == ',') {
                        packet.list.push_back(read_packet(s.substr(last_comma + 1, i - (last_comma + 1))));
                        last_comma = i;
                    }
                }
            }
            packet.list.push_back(read_packet(s.substr(last_comma + 1, s.size() - 1 - (last_comma + 1))));
        }
    } else {
        packet.number = std::stoi(s);
    }
    return packet;
}

int compare(Packet a, Packet b) {
    if (a.number != -1 && b.number != -1) {
        return a.number - b.number;
    } else if (a.number != -1) {
        Packet tmp;
        tmp.number = -1;
        tmp.list.push_back(a);
        a = tmp;
    } else if (b.number != -1) {
        Packet tmp;
        tmp.number = -1;
        tmp.list.push_back(b);
        b = tmp;
    }
    for (int i = 0; i < a.list.size() && i < b.list.size(); i++) {
        int c = compare(a.list[i], b.list[i]);
        if (c != 0) {
            return c;
        }
    }
    return (int) a.list.size() - (int) b.list.size();
}

void aoc13() {
    std::vector<std::string> input = read("../input/13.txt");
    std::vector<Packet> packets;
    int sum = 0;
    int idx = 0;
    for (int i = 0; i < input.size(); i++) {
        idx++;
        Packet a = read_packet(input[i]);
        i++;
        Packet b = read_packet(input[i]);
        i++;
        if (compare(a, b) < 0) {
            sum += idx;
        }
        packets.push_back(a);
        packets.push_back(b);
    }
    std::cout << sum << std::endl;

    Packet divider2 = read_packet("[[2]]");
    Packet divider6 = read_packet("[[6]]");
    packets.push_back(divider2);
    packets.push_back(divider6);
    std::sort(packets.begin(), packets.end(), [](Packet a, Packet b) {
        return compare(a, b) < 0;
    });
    int decoder_key = 1;
    idx = 0;
    for (int i = 0; i < packets.size(); i++) {
        idx++;
        if (compare(packets[i], divider2) == 0 || compare(packets[i], divider6) == 0) {
            decoder_key *= idx;
        }
    }
    std::cout << decoder_key << std::endl;
}
