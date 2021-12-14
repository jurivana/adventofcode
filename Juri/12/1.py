import os
from collections import defaultdict

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

connections = defaultdict(list)
for line in input:
    cave_1, cave_2 = line.split('-')
    connections[cave_1].append(cave_2)
    connections[cave_2].append(cave_1)


def visit_cave(cave: str, visited: list):
    global paths
    if cave == 'end':
        paths += 1
        return
    if cave.islower():
        visited.append(cave)
    for con in connections[cave]:
        if con not in visited:
            visit_cave(con, visited[:])


paths = 0
visited = ['start']
for cave in connections['start']:
    visit_cave(cave, visited[:])

print(paths)
