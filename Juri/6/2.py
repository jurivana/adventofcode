from collections import defaultdict
import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()[0]

input = [int(fish) for fish in input.split(',')]
lanternfish = defaultdict(int)
for fish in input:
    if fish not in lanternfish:
        lanternfish[fish] = 0
    lanternfish[fish] += 1
    
for _ in range(256):
    tmp = defaultdict(int)
    for fish, cnt in lanternfish.items():
        if fish == 0:
            tmp[6] += cnt
            tmp[8] += cnt
        else:
            tmp[fish - 1] += cnt
    lanternfish = tmp

print(sum(lanternfish.values()))