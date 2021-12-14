import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

dots = set()
for line in input:
    if not line:
        continue
    try:
        x, y = line.split(',')
        dots.add((int(x), int(y)))
    except ValueError:
        fold = line.split()[2]
        dimension, line = fold.split('=')
        line = int(line)
        index = 0 if dimension == 'x' else 1
        for dot in dots.copy():
            if dot[index] > line:
                dots.remove(dot)
                dot = list(dot)
                dot[index] = 2 * line - dot[index]
                dots.add((dot[0], dot[1]))

for y in range(max(dots, key=lambda x: x[1])[1] + 1):
    for x in range(max(dots, key=lambda x: x[0])[0] + 1):
        print('#' if (x, y) in dots else '.', end='')
    print()
