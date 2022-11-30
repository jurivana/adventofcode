import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()[0]

lanternfish = [int(fish) for fish in input.split(',')]

for _ in range(80):
    for i in range(len(lanternfish) - 1, -1, -1):
        lanternfish[i] -= 1
        if lanternfish[i] == -1:
            lanternfish[i] = 6
            lanternfish.append(8)

print(len(lanternfish))