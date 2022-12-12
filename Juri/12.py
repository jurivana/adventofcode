import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

map = []
start = None
a_fields = []
end = None
for y, line in enumerate(input):
    heights = []
    for x, height in enumerate(line):
        if height == 'S':
            start = (y, x)
            heights.append(0)
        elif height == 'E':
            end = (y, x)
            heights.append(25)
        else:
            heights.append(ord(height) - ord('a'))
        if height == 'a':
            a_fields.append((y, x))
    map.append(heights)


def manhattan_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def print_path(path):
    for y in range(len(map)):
        for x in range(len(map[0])):
            print('*' if (y, x) in path else '-', end='')
        print()


def get_shortest_path(paths):
    visited = set()
    while paths:
        paths.sort(key=lambda path: (path[1] + path[2], path[2]))
        pos, cost, _, prev = paths.pop(0)
        visited.add(pos)
        for d in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            ny = pos[0] + d[0]
            nx = pos[1] + d[1]
            if not (0 <= nx < len(map[0]) and 0 <= ny < len(map)) or (ny, nx) in visited or map[ny][nx] - map[pos[0]][pos[1]] > 1:
                continue

            already_added = False
            for path in paths[:]:
                if path[0] == (ny, nx):
                    if path[1] > cost + 1:
                        paths.remove(path)
                    else:
                        already_added = True
            if already_added:
                continue

            if (ny, nx) == end:
                # print_path(prev + ((ny, nx),))
                return cost + 1

            paths.append(((ny, nx), cost + 1, manhattan_dist((ny, nx), end), prev + (pos,)))


def part_1():
    return get_shortest_path([(start, 0, manhattan_dist(start, end), (start,))])


def part_2():
    paths = [(field, 0, manhattan_dist(field, end), (field,)) for field in a_fields]
    return get_shortest_path(paths)


print(globals()[f'part_{sys.argv[1]}']())
