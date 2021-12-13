#!/usr/bin/python3
import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = sorted([int(x) for x in f.read().splitlines()[0].split(',')])

best = float('inf')
for med in range(2000):
    score = 0
    for x in input:
        diff = abs(x-med)
        score += diff*(diff+1)/2
    if score < best:
        best = score
print(int(best))