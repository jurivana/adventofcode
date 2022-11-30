import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = [int(i) for i in f.readlines()]
    result = 0
    for prev, curr in zip(input, input[1:]):
        if curr > prev:
            result = result + 1
    print(result)
