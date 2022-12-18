from collections import defaultdict
import sys
import os
from read import read
from pathlib import Path


file = Path(os.path.abspath(__file__)).stem
input = read(file)

# Steine von unten links
rocks = (
    ((0, 0), (0, 1), (0, 2), (0, 3)),
    ((0, 1), (1, 0), (1, 1), (1, 2), (2, 1)),
    ((2, 2), (1, 2), (0, 0), (0, 1), (0, 2)),
    ((0, 0), (1, 0), (2, 0), (3, 0)),
    ((0, 0), (0, 1), (1, 0), (1, 1))
)
height = 0
i = 0
chamber = [defaultdict(bool) for _ in range(7)]
for c in range(7):
    chamber[c][0] = True


def move_rock(pos, direction, rock) -> bool:
    global chamber
    npos = (pos[0] + direction[0], pos[1] + direction[1])
    for r, c in rock:
        pr, pc = [npos[0] + r, npos[1] + c]
        if not (0 <= pc <= 6) or chamber[pc][pr]:
            return pos, False
    return npos, True


def stop_rock(pos, rock):
    global height
    global chamber
    for r, c in rock:
        pr, pc = [pos[0] + r, pos[1] + c]
        chamber[pc][pr] = True
        height = max(height, pr)


def sim_rock(rock) -> int:
    global chamber
    global i
    pos = [height + 4, 2]
    while True:
        command = input[i % len(input)]
        i += 1

        direction = 1 if command == '>' else -1
        pos, _ = move_rock(pos, (0, direction), rock)

        pos, moved = move_rock(pos, (-1, 0), rock)
        if not moved:
            stop_rock(pos, rock)
            break
    return height


def top_view():
    cols = []
    for col in chamber:
        h = 0
        for key, occ in col.items():
            if occ:
                h = max(h, key)
        cols.append(height - h)
    return tuple(cols)


def repeat(prev_height, prev_r, r):
    global height
    global chamber
    repeat = (1000000000000 - r) // (r - prev_r)
    extra_height = repeat * (height - prev_height)
    r += repeat * (r - prev_r)

    return r, extra_height


def part_1():
    for r in range(2022):
        rock = rocks[r % 5]
        sim_rock(rock)
    return height


def part_2():
    global height
    seen = {}
    r = 0
    while r < 1000000000000:
        rock = rocks[r % 5]
        cmd_pos = i % len(input)
        tv = top_view()
        if (tv, rock, cmd_pos) in seen:
            prev_height, prev_r = seen[(tv, rock, cmd_pos)]
            r, extra_height = repeat(prev_height, prev_r, r)
            seen = {}
        seen[(tv, rock, cmd_pos)] = (height, r)
        sim_rock(rock)
        r += 1
    return height + extra_height


print(globals()[f'part_{sys.argv[1]}']())
