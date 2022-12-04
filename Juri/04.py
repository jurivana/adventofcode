import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

def get_ranges(line):
    elf1, elf2 = line.split(',')
    min1, max1 = map(int, elf1.split('-'))
    min2, max2 = map(int, elf2.split('-'))
    return min1, max1, min2, max2

def part_1():
    count = 0
    for line in input:
        min1, max1, min2, max2 = get_ranges(line)
        if (min1 <= min2 and max1 >= max2) or (min1 >= min2 and max1 <= max2):
            count += 1

    return count


def part_2():
    count = 0
    for line in input:
        min1, max1, min2, max2 = get_ranges(line)
        if max(min1, min2) <= min(max1, max2):
            count += 1
    return count


print(globals()[f'part_{sys.argv[1]}']())
