import sys
import os
from read import read
from pathlib import Path
from collections import defaultdict

file = Path(os.path.abspath(__file__)).stem
input = [line.split() for line in read(file).splitlines()]

directories = defaultdict(int)
curr_dirs = ['']
for line in input:
    if line[0] == '$' and line[1] == 'cd':
        if line[2] == '/':
            curr_dirs = ['']
        elif line[2] == '..':
            curr_dirs.pop()
        else:
            curr_dirs.append(line[2])
    elif line[0].isdigit():
        path = ''
        for dir in curr_dirs:
            path += dir + '/'
            directories[path] += int(line[0])


def part_1():
    return sum([size for size in directories.values() if size <= 100_000])


def part_2():
    return min([size for size in directories.values() if size > directories['/'] - 40_000_000])


print(globals()[f'part_{sys.argv[1]}']())
