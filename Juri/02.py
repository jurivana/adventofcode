import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()


def get_moves(round):
    col1, col2 = [ord(move) for move in round.split(' ')]
    col1 -= ord('A')
    col2 -= ord('X')
    return col1, col2


def part_1():
    score = 0
    for round in input:
        opponent, me = get_moves(round)
        me += 1
        score += me + 3 * ((me - opponent) % 3)

    return score


def part_2():
    score = 0
    for round in input:
        opponent, result = get_moves(round)
        me = (opponent + result - 1) % 3 + 1
        score += me + 3 * result

    return score


print(globals()[f'part_{sys.argv[1]}']())
