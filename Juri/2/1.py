import os

commands = {"forward": [1, 0], "down": [0, 1], "up": [0, -1]}

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.readlines()
    position = [0, 0]
    for line in input:
        command, value = line.split()
        position = [prev + instruction for prev, instruction in zip(position, [x * int(value) for x in commands[command]])]
    print(position[0] * position[1])
