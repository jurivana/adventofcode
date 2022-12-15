import sys
import os
from read import read
from pathlib import Path
import re

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()


def manhattan_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def part_1():
    y = 20000
    occ = set()
    for line in input:
        sx, sy, bx, by = map(int, re.findall(r'-?\d+', line))
        dist = manhattan_dist((sx, sy), (bx, by))
        max_x_dist = dist - abs(sy - y)
        if max_x_dist < 0:
            continue
        for x in range(sx - max_x_dist, sx + max_x_dist + 1):
            if (x, y) != (bx, by):
                occ.add(x)
    return len(occ)


def part_2():
    max_range = 4000000
    options = [[(0, max_range)] for _ in range(max_range + 1)]
    for line in input:
        sx, sy, bx, by = map(int, re.findall(r'-?\d+', line))
        dist = manhattan_dist((sx, sy), (bx, by))
        for y in range(sy - dist, sy + dist + 1):
            if not (0 <= y <= max_range):
                continue
            max_x_dist = dist - abs(sy - y)
            if max_x_dist < 0:
                continue
            min_sx, max_sx = sx - max_x_dist, sx + max_x_dist
            for min_x, max_x in options[y][:]:
                # Außen
                if min_sx <= min_x and max_sx >= max_x:
                    pass
                # Mittendrin
                elif min_sx >= min_x and max_sx <= max_x:
                    options[y].append((min_x, min_sx - 1))
                    options[y].append((max_sx + 1, max_x))
                # Am rechten Ende
                elif min_sx >= min_x and min_sx <= max_x:
                    options[y].append((min_x, min_sx - 1))
                # Am linken Ende
                elif min_sx <= min_x and max_sx >= min_x:
                    options[y].append((max_sx + 1, max_x))
                # Nicht drin
                else:
                    continue
                options[y].remove((min_x, max_x))

    for x, y in enumerate(options):
        if y:
            return x + 4000000 * y[0][0]


print(globals()[f'part_{sys.argv[1]}']())
