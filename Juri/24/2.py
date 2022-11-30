import os
from typing import Union

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

stack = []
model_number = [None for _ in range(14)]
for i in range(14):
    check = int(input[i * 18 + 5].split()[2])
    offset = int(input[i * 18 + 15].split()[2])
    if check > 0:
        stack.append((i, offset))
    else:
        idx, val = stack.pop()
        if val + check > 0:
            model_number[idx] = 1
            model_number[i] = 1 + val + check
        else:
            model_number[i] = 1
            model_number[idx] = 1 - val - check
print(''.join([str(d) for d in model_number]))
