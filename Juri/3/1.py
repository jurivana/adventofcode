import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()
    gamma = [0 for _ in range(len(input[0]))]
    for number in input:
        for i in range(len(number)):
            gamma[i] += int(number[i])
    gamma = [1 if one_bits > len(input) / 2 else 0 for one_bits in gamma]
    epsilon = [1 if x == 0 else 0 for x in gamma]
    print(int(''.join(str(bit) for bit in gamma), 2) * int(''.join(str(bit) for bit in epsilon), 2))
