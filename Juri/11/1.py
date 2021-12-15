import os

row_diff = [-1, 1, 0, 0, -1, 1, -1, 1]
col_diff = [0, 0, -1, 1, -1, 1, 1, -1]

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

dumbos = [[int(dumbo) for dumbo in line] for line in input]
rows = len(dumbos)
cols = len(dumbos[0])
flashes = 0


def increase(row, col):
    global flashes
    dumbos[row][col] += 1
    if dumbos[row][col] == 10:
        flashes += 1
        for d in range(8):
            r = row + row_diff[d]
            c = col + col_diff[d]
            if 0 <= r < rows and 0 <= c < cols:
                increase(r, c)


steps = 0
while True:
    all_flashed = True
    for row in range(rows):
        for col in range(cols):
            increase(row, col)
    for row in range(rows):
        for col in range(cols):
            if dumbos[row][col] > 9:
                dumbos[row][col] = 0
            else:
                all_flashed = False
    steps += 1
    if all_flashed:
        print(steps)
        break
