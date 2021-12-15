import os
from collections import defaultdict

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

connections = defaultdict(list)
for line in input:
    cave_1, cave_2 = line.split('-')
    connections[cave_1].append(cave_2)
    connections[cave_2].append(cave_1)


def visit_cave(cave: str, visited: list, double_used: bool, must_visit: str):
    global paths
    if cave == must_visit:
        must_visit = None
    if cave == 'end' and not must_visit:
        paths += 1
        return
    if cave.islower():
        visited.append(cave)
    for con in connections[cave]:
        if con not in visited:
            visit_cave(con, visited[:], double_used, must_visit)
            if cave.islower() and not double_used:
                new_visited = visited[:]
                new_visited.remove(cave)
                visit_cave(con, new_visited[:], True, cave)


paths = 0
visited = ['start']
for cave in connections['start']:
    visit_cave(cave, visited[:], False, None)

print(paths)
