import os

commands = {"forward": [1, 1, 0], "down": [0, 0, 1], "up": [0, 0, -1]}

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.readlines()
    position = [0, 0, 0]
    for line in input:
        command, value = line.split()
        aim = [1, position[2], 1]
        position = [prev + instruction for prev, instruction in zip(position, [x * int(value) * y for x, y in zip(commands[command], aim)])]
    print(position[0] * position[1])
