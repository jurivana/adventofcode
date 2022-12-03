import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file)


def part_1():
    pass


def part_2():
    pass


print(globals()[f'part_{sys.argv[1]}']())
