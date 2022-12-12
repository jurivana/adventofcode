#pragma once

#include "util.h"

struct Monkey {
    std::queue<ll> items;
    std::function<ll(ll)> operation;
    ll divisor;
    int next_true;
    int next_false;
};

ll monkey_business(std::vector<Monkey> monkeys, int n, bool worry) {
    ll mod = 1;
    for (int i = 0; i < monkeys.size(); i++) {
        mod *= monkeys[i].divisor;
    }
    std::vector<ll> n_inspected(monkeys.size(), 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < monkeys.size(); j++) {
            while (!monkeys[j].items.empty()) {
                ll item = monkeys[j].items.front();
                monkeys[j].items.pop();
                item = monkeys[j].operation(item);
                if (worry) {
                    item %= mod;
                } else {
                    item /= 3;
                }
                monkeys[item % monkeys[j].divisor == 0 ? monkeys[j].next_true : monkeys[j].next_false].items.push(item);
                n_inspected[j]++;
            }
        }
    }
    std::sort(n_inspected.begin(), n_inspected.end());
    ll monkey_business = 1;
    for (int i = 0; i < 2; i++) {
        monkey_business *= n_inspected[n_inspected.size() - 1 - i];
    }
    return monkey_business;
}

void aoc11() {
    std::vector<std::string> input = read("../input/11.txt");
    std::vector<Monkey> monkeys;
    for (int i = 0; i < input.size(); i++) {
        Monkey monkey;
        i++;                   // Monkey x:
        input[i].erase(0, 18); //   Starting items:
        bool end = false;
        while (!end) {
            int pos = input[i].find(",");
            if (pos == std::string::npos) {
                pos = input.size();
                end = true;
            }
            monkey.items.push(std::stol(input[i].substr(0, pos)));
            input[i].erase(0, pos + 2);
        }
        i++;
        input[i].erase(0, 19); //   Operation: new =
        std::string term = input[i];
        monkey.operation = [term](ll old) {
            std::function<ll(std::string)> operand = [old](std::string s) {
                ll x;
                if (s == "old") {
                    x = old;
                } else {
                    x = std::stol(s);
                }
                return x;
            };
            int pos = term.find(" ");
            ll a = operand(term.substr(0, pos));
            ll b = operand(term.substr(pos + 3, term.size()));
            if (term.at(pos + 1) == '+') {
                return a + b;
            } else {
                return a * b;
            }
        };
        i++;
        input[i].erase(0, 21); //   Test: divisible by
        monkey.divisor = std::stoi(input[i]);
        i++;
        input[i].erase(0, 29); //     If true: throw to monkey
        monkey.next_true = std::stoi(input[i]);
        i++;
        input[i].erase(0, 30); //     If false: throw to monkey
        monkey.next_false = std::stoi(input[i]);
        i++;
        monkeys.push_back(monkey);
    }
    std::cout << monkey_business(monkeys, 20, false) << std::endl;
    std::cout << monkey_business(monkeys, 10000, true) << std::endl;
}
