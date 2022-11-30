from heapq import *
import os

rd = [-1, 1, 0, 0]
cd = [0, 0, -1, 1]

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

init_risk_map = [[int(risk) for risk in line] for line in input]
init_rows = len(init_risk_map)
init_cols = len(init_risk_map[0])
risk_map = [[None for _ in range(5 * init_cols)] for _ in range(5 * init_rows)]
for row in range(len(risk_map)):
    for col in range(len(risk_map)):
        risk_map[row][col] = (init_risk_map[row % init_rows][col % init_cols] + row // init_rows + col // init_cols - 1) % 9 + 1
risk_map[0][0] = 0

rows = len(risk_map)
cols = len(risk_map[0])
destination = (rows - 1, cols - 1)
nodes = [(0, 0, 0)]
dist = [[None for _ in range(cols)] for _ in range(rows)]

while nodes:
    curr_dist, row, col = heappop(nodes)
    if not (0 <= row < rows and 0 <= col < cols):
        continue

    if dist[row][col] is None or curr_dist + risk_map[row][col] < dist[row][col]:
        dist[row][col] = curr_dist + risk_map[row][col]
    else:
        continue

    if (row, col) == destination:
        print(dist[row][col])
        break

    for d in range(4):
        new_row = row + rd[d]
        new_col = col + cd[d]
        heappush(nodes, (dist[row][col], new_row, new_col))
