import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()
N = len(input)
indices = list(range(N))


def mix(numbers, times=1):
    for i in indices * times:
        idx = indices.index(i)
        indices.insert((idx + numbers[i]) % (N - 1), indices.pop(idx))

    zero = indices.index(numbers.index(0))
    return sum(numbers[indices[(zero+p) % N]] for p in [1000, 2000, 3000])


def part_1():
    numbers = [int(x) for x in input]
    return mix(numbers)


def part_2():
    numbers = [int(x) * 811589153 for x in input]
    return mix(numbers, 10)


print(globals()[f'part_{sys.argv[1]}']())
