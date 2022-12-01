import sys
import os
import heapq
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).split('\n\n')


def part_1():
    max_calories = 0
    for elf in input:
        max_calories = max(max_calories, sum([int(calories) for calories in elf.splitlines()]))

    return max_calories


def part_2():
    calories = []
    for elf in input:
        heapq.heappush(calories, sum([int(calories) for calories in elf.splitlines()]))
        
    return sum(heapq.nlargest(3, calories))


print(globals()[f'part_{sys.argv[1]}']())
