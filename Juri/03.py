import sys
import os
from read import read
from pathlib import Path


file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

def get_priority(item: str) -> int:
    prio_offset = ord('a') - 1 if item.islower() else ord('A') - 27
    return ord(item) - prio_offset

def part_1():
    priorities = 0
    for rucksack in input:
        dep1, dep2 = rucksack[:len(rucksack) // 2], rucksack[len(rucksack) // 2:]
        for item in dep1:
            if item in dep2:
                priorities += get_priority(item)
                break
    return priorities


def part_2():
    priorities = 0
    for group in range(0, len(input), 3):
        for item in input[group]:
            if item in input[group + 1] and item in input[group + 2]:
                priorities += get_priority(item)
                break
    return priorities



print(globals()[f'part_{sys.argv[1]}']())
