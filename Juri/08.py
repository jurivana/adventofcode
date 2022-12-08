import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()


def part_1():
    visible = 0
    for r in range(len(input)):
        for c in range(len(input[0])):
            visible += any((
                all([input[r][c] > tree for tree in input[r][:c]]),    # links
                all([input[r][c] > tree for tree in input[r][c+1:]]),  # rechts
                all([input[r][c] > row[c] for row in input[:r]]),      # oben
                all([input[r][c] > row[c] for row in input[r+1:]])     # unten
            ))

    return visible


def part_2():
    max_score = 0
    for r in range(len(input)):
        for c in range(len(input[0])):
            if r == 0 or c == 0 or r == len(input) - 1 or c == len(input[0]) - 1:
                continue
            scenic_score = (
                (int(([i for i, tree in enumerate(input[r][c-1::-1]) if tree >= input[r][c]] or [c-1])[0]) + 1) *             # links
                (int(([i for i, tree in enumerate(input[r][c+1:]) if tree >= input[r][c]] or [len(input[0])-c-2])[0]) + 1) *  # rechts
                (int(([i for i, row in enumerate(input[r-1::-1]) if row[c] >= input[r][c]] or [r-1])[0]) + 1) *               # oben
                (int(([i for i, row in enumerate(input[r+1:]) if row[c] >= input[r][c]] or [len(input)-r-2])[0]) + 1)         # unten
            )
            max_score = max(scenic_score, max_score)

    return max_score


print(globals()[f'part_{sys.argv[1]}']())
