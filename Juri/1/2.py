import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = [int(i) for i in f.readlines()]
    result = 0
    for values in zip(input, input[1:], input[2:], input[3:]):
        prev = sum(values[:-1])
        curr = sum(values[1:])
        if curr > prev:
            result = result + 1
    print(result)
