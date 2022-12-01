import sys
import os
import heapq
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).split('\n\n')


def get_calories() -> list[int]:
    return [sum([int(calories) for calories in elf.splitlines()]) for elf in input]


def part_1() -> int:
    return max(get_calories())


def part_2() -> int:
    return sum(sorted(get_calories())[-3:])


print(globals()[f'part_{sys.argv[1]}']())
