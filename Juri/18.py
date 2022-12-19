import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

cubes: set[tuple[int, int, int]] = set()
for line in input:
    cubes.add(tuple(map(int, line.split(','))))


def sides(cube):
    for d in (-1, 1):
        for i in range(3):
            yield tuple([c + d if j == i else c for j, c in enumerate(list(cube))])


def part_1():
    return sum(side not in cubes for cube in cubes for side in sides(cube))


def part_2():
    steam = set()
    bounding_box = (
        (min([c[0] for c in cubes]) - 1, max([c[0] for c in cubes]) + 1),
        (min([c[1] for c in cubes]) - 1, max([c[1] for c in cubes]) + 1),
        (min([c[2] for c in cubes]) - 1, max([c[2] for c in cubes]) + 1)
    )
    queue = [(bounding_box[0][0], bounding_box[1][0], bounding_box[2][0])]
    while queue:
        cube = queue.pop()
        in_bounding_box = all(bounding_box[i][0] <= cube[i] <= bounding_box[i][1] for i in range(3))
        queue += [side for side in sides(cube) if side not in cubes and side not in steam and in_bounding_box]
        steam.add(cube)
    return sum(side in steam for cube in cubes for side in sides(cube))


print(globals()[f'part_{sys.argv[1]}']())
