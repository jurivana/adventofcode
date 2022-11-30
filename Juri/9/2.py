from collections import deque
import os

row_diff = [-1, 1, 0, 0]
col_diff = [0, 0, -1, 1]

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

heightmap = []
for line in input:
    heightmap.append([int(height) for height in list(line)])

basin_sizes = []
for row, heightline in enumerate(heightmap):
    for col, heightpoint in enumerate(heightline):
        if heightpoint == 9:
            continue
        size = 0
        queue = deque()
        queue.append((row, col))
        while queue:
            (r, c) = queue.popleft()
            if heightmap[r][c] == 9:
                continue
            heightmap[r][c] = 9
            size += 1
            for d in range(4):
                rd = r + row_diff[d]
                cd = c + col_diff[d]
                if 0 <= rd < len(heightmap) and 0 <= cd < len(heightline):
                    queue.append((rd, cd))
        basin_sizes.append(size)

basin_sizes.sort()
print(basin_sizes[-1] * basin_sizes[-2] * basin_sizes[-3])
