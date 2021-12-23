import os
from itertools import product

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()


def get_range(string: str):
    lower, upper = string.split('=')[1].split('..')
    return int(lower), int(upper) + 1


X_COORDS = []
Y_COORDS = []
Z_COORDS = []
STEPS = []
for line in input:
    x, y, z = line[3:].split(',')
    x0, x1 = get_range(x)
    y0, y1 = get_range(y)
    z0, z1 = get_range(z)
    value = line[:2] == 'on'

    STEPS.append([x0, x1, y0, y1, z0, z1, value])
    X_COORDS.extend([x0, x1])
    Y_COORDS.extend([y0, y1])
    Z_COORDS.extend([z0, z1])


X_COORDS.sort()
Y_COORDS.sort()
Z_COORDS.sort()
N = len(X_COORDS)

GRID = [[[0 for _ in range(N)] for _ in range(N)] for _ in range(N)]
for step in STEPS:
    x0, x1, y0, y1, z0, z1, value = step
    x0 = X_COORDS.index(x0)
    x1 = X_COORDS.index(x1)
    y0 = Y_COORDS.index(y0)
    y1 = Y_COORDS.index(y1)
    z0 = Z_COORDS.index(z0)
    z1 = Z_COORDS.index(z1)

    for x in range(x0, x1):
        for y in range(y0, y1):
            for z in range(z0, z1):
                GRID[x][y][z] = value


sum = 0
for x in range(N - 1):
    for y in range(N - 1):
        for z in range(N - 1):
            x_range = X_COORDS[x + 1] - X_COORDS[x]
            y_range = Y_COORDS[y + 1] - Y_COORDS[y]
            z_range = Z_COORDS[z + 1] - Z_COORDS[z]
            sum += GRID[x][y][z] * x_range * y_range * z_range

print(sum)
