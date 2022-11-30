import os
from itertools import cycle

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

vents = [[0 for _ in range(1000)] for _ in range(1000)]
for line in input:
    [x1, y1], [x2, y2] = [[int(n[0]), int(n[1])] for n in [pos.split(',') for pos in line.split(' -> ')]]
    x_direction = 1 if x1 < x2 else -1
    y_direction = 1 if y1 < y2 else -1
    x_range = range(x1, x2 + x_direction, x_direction)
    y_range = range(y1, y2 + y_direction, y_direction)
    x_cycle = cycle(x_range) if len(x_range) < len(y_range) else x_range
    y_cycle = cycle(y_range) if len(y_range) < len(x_range) else y_range
    for x, y in zip(x_cycle, y_cycle):
        vents[y][x] += 1

print(sum([len(list(filter(lambda n: n > 1, x))) for x in vents]))