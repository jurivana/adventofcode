import os
from statistics import median
from functools import reduce

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = [int(x) for x in f.read().splitlines()[0].split(',')]

print(reduce(lambda fuel, crab: fuel + abs(crab - int(median(input))), input, 0))