from itertools import zip_longest
import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

blocked = set()
lowest = 0
cnt = 0
for line in input:
    rock_coords = line.split(' -> ')
    prev = rock_coords[0]
    for coords in rock_coords[1:]:
        x1, y1 = map(int, prev.split(','))
        x2, y2 = map(int, coords.split(','))
        x_dir = 1 if x1 <= x2 else -1
        y_dir = 1 if y1 <= y2 else -1
        lowest = max(lowest, y1, y2)
        for x, y in zip_longest(range(x1, x2 + x_dir, x_dir), range(y1, y2 + y_dir, y_dir)):
            blocked.add((x if x else x1, y if y else y1))
        prev = coords


def sim_sand(sand) -> tuple[tuple[int, int], bool]:
    global blocked
    global cnt
    sand_d = (sand[0], sand[1] + 1)
    sand_dl = (sand[0] - 1, sand[1] + 1)
    sand_dr = (sand[0] + 1, sand[1] + 1)
    if sand_d not in blocked:
        sand = sand_d
    elif sand_dl not in blocked:
        sand = sand_dl
    elif sand_dr not in blocked:
        sand = sand_dr
    else:
        blocked.add(sand)
        cnt += 1
        return sand, True
    return sand, False


def part_1():
    sand = (500, 0)
    while True:
        if sand[1] == lowest:
            return cnt
        pos, rested = sim_sand(sand)
        sand = pos
        if rested:
            sand = (500, 0)


def part_2():
    global cnt
    sand = (500, 0)
    while True:
        if sand[1] == lowest + 1:
            blocked.add(sand)
            cnt += 1
            sand = (500, 0)
        pos, rested = sim_sand(sand)
        sand = pos
        if rested:
            if pos == (500, 0):
                return cnt
            sand = (500, 0)


print(globals()[f'part_{sys.argv[1]}']())
