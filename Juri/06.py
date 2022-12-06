import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file)


def marker_pos(length):
    for i in range(len(input) - length):
        if len(set(input[i:i+length])) == length:
            return length + i


def part_1():
    return marker_pos(4)


def part_2():
    return marker_pos(14)


print(globals()[f'part_{sys.argv[1]}']())
