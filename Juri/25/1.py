import os
from copy import deepcopy

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

MAP = [[space for space in line] for line in input]
R = len(MAP)
C = len(MAP[0])

MOVE = {'>': [0, 1], 'v': [1, 0]}


def get_move(r, c, h):
    rd, cd = MOVE[h]
    r = (r + rd) % R
    c = (c + cd) % C
    return r, c


i = 0
while True:
    prev = deepcopy(MAP)
    for h in ['>', 'v']:
        m = deepcopy(MAP)
        for r in range(R):
            for c in range(C):
                if MAP[r][c] == h:
                    nr, nc = get_move(r, c, h)
                    if MAP[nr][nc] == '.':
                        m[r][c] = '.'
                        m[nr][nc] = h
        MAP = m
    i += 1
    if prev == MAP:
        print(i)
        break
