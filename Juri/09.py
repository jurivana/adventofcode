from math import ceil
import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = [[line.split()[0], int(line.split()[1])] for line in read(file).splitlines()]
directions = {
    'D': (-1,  0),
    'U': (1,  0),
    'L': (0, -1),
    'R': (0,  1)
}


def calc_pos(front, back):
    y_diff = front[0] - back[0]
    x_diff = front[1] - back[1]
    if abs(y_diff) == 2:
        back[0] += y_diff // 2
        if abs(x_diff) >= 1:
            back[1] += (x_diff // x_diff) * -1 if x_diff < 0 else 1
    elif abs(x_diff) == 2:
        back[1] += x_diff // 2
        if abs(y_diff) >= 1:
            back[0] += (y_diff // y_diff) * -1 if y_diff < 0 else 1


def tail_positions(length):
    knots = [[0, 0] for _ in range(length)]
    visited = set()
    for direction, times in input:
        for _ in range(times):
            move = directions[direction]
            knots[0] = [knots[0][i] + move[i] for i in range(2)]
            for i in range(length - 1):
                calc_pos(knots[i], knots[i + 1])
            visited.add(tuple(knots[-1]))
    return len(visited)


def part_1():
    return tail_positions(2)


def part_2():
    return tail_positions(10)


print(globals()[f'part_{sys.argv[1]}']())
