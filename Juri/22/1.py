import os
from itertools import product

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()


def get_range(string: str):
    lower, upper = string.split('=')[1].split('..')
    return range(int(lower), int(upper)+1)


CUBES = set()
for line in input[:20]:
    x, y, z = line[3:].split(',')
    cubes = product(list(get_range(x)), list(get_range(y)), list(get_range(z)))
    for cube in cubes:
        if line[:2] == 'on':
            CUBES.add(cube)
        else:
            CUBES.discard(cube)

print(len(CUBES))
