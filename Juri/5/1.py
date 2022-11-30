import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

vents = [[0 for _ in range(1000)] for _ in range(1000)]
for line in input:
    [x1, y1], [x2, y2] = [[int(n[0]), int(n[1])] for n in [pos.split(',') for pos in line.split(' -> ')]]
    if x1 == x2:
        direction = 1 if y1 < y2 else -1
        for y in range(y1, y2 + direction, direction):
            vents[y][x1] += 1
    elif y1 == y2:
        direction = 1 if x1 < x2 else -1
        for x in range(x1, x2 + direction, direction):
            vents[y1][x] += 1
print(sum([len(list(filter(lambda n: n > 1, x))) for x in vents]))