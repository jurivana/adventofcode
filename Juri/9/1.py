import os

row_diff = [-1, 1, 0, 0]
col_diff = [0, 0, -1, 1]

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

heightmap = []
for line in input:
    heightmap.append([int(height) for height in list(line)])

risk = 0
for row, heightline in enumerate(heightmap):
    for col, heightpoint in enumerate(heightline):
        adj_locs = []
        for d in range(4):
            rd = row + row_diff[d]
            cd = col + col_diff[d]
            adj_locs.append(heightmap[rd][cd] if 0 <= rd < len(heightmap) and 0 <= cd < len(heightline) else float('inf'))
        if all([loc > heightpoint for loc in adj_locs]):
            risk += heightpoint + 1

print(risk)
