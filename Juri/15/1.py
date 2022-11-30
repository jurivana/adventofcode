from collections import defaultdict
import os

rd = [-1, 1, 0, 0]
cd = [0, 0, -1, 1]

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

risk_map = [[int(risk) for risk in line] for line in input]
rows = len(risk_map)
cols = len(risk_map[0])
destination = (rows - 1, cols - 1)
nodes = defaultdict(dict)
for r in range(rows):
    for c in range(cols):
        nodes[(r, c)]['dist'] = float('inf')
        nodes[(r, c)]['visited'] = False
nodes[(0, 0)]['dist'] = 0

while True:
    [(row, col), values] = min(filter(lambda x: not x[1]['visited'], nodes.items()), key=lambda x: x[1]['dist'])
    curr_dist = values['dist']
    if (row, col) == destination:
        print(curr_dist)
        break
    nodes[(row, col)]['visited'] = True
    for d in range(4):
        new_row = row + rd[d]
        new_col = col + cd[d]
        if 0 <= new_row < rows and 0 <= new_col < cols and (new_row, new_col) in nodes:
            new_dist = curr_dist + risk_map[new_row][new_col]
            nodes[(new_row, new_col)]['dist'] = min(nodes[(new_row, new_col)]['dist'], new_dist)
