from __future__ import annotations
import sys
import os
from read import read
from pathlib import Path
from typing import Callable
import re
import operator


file = Path(os.path.abspath(__file__)).stem
input = [monkey.splitlines() for monkey in read(file).split('\n\n')]

OPS = {
    '+': operator.add,
    '*': operator.mul
}


class Monkey:
    def __init__(self, items: list[int], op, it, test_div, throw_true, throw_false, part):
        self.items = items
        self.operation = lambda item: OPS[op](item, int(it) if it != 'old' else item)
        self.test_div = test_div
        self.throw = lambda item: throw_true if item % test_div == 0 else throw_false
        self.part = part
        self.inspections = 0

    def turn(self, monkeys: list[Monkey], mod=None) -> None:
        while self.items:
            item = self.items.pop(0)
            if mod:
                item = item % mod
            item = self.operation(item)
            if self.part == 1:
                item = item // 3
            self.inspections += 1
            monkeys[self.throw(item)].items.append(item)


def run(part):
    monkeys: list[Monkey] = []
    mod = 1
    for monkey_input in input:
        op_input = monkey_input[2].split()
        test_div = int(monkey_input[3].split()[-1])
        mod *= test_div
        throw_true = int(monkey_input[4].split()[-1])
        throw_false = int(monkey_input[5].split()[-1])
        monkeys.append(Monkey(
            items=list(map(int, re.findall(r'\d+', monkey_input[1]))),
            op=op_input[-2],
            it=op_input[-1],
            test_div=test_div,
            throw_true=throw_true,
            throw_false=throw_false,
            part=part
        ))

    for _ in range(20 if part == 1 else 10000):
        for monkey in monkeys:
            monkey.turn(monkeys, mod)
    inspections = sorted([monkey.inspections for monkey in monkeys])
    return inspections[-2] * inspections[-1]


def part_1():
    return run(1)


def part_2():
    return run(2)


print(globals()[f'part_{sys.argv[1]}']())
