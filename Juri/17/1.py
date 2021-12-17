import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()[0]

target_x, target_y = input.split(': ')[1].split(', ')
target_xmin, target_xmax = [int(n) for n in target_x[2:].split('..')]
target_ymin, target_ymax = [int(n) for n in target_y[2:].split('..')]

lower_x = None
for x in range(target_xmax):
    if (x * (x + 1)) / 2 >= target_xmin:
        lower_x = x
        break

ovr_ymax = 0
for x in range(lower_x, target_xmax + 1):
    for y in range(target_ymin, -target_ymin):
        xpos = 0
        ypos = 0
        dx = x
        dy = y
        ymax = 0
        for t in range(max(lower_x, -2 * target_ymin + 1)):
            xpos += dx
            ypos += dy
            dx -= dx // abs(dx) if dx != 0 else 0
            dy -= 1
            if ypos > ymax:
                ymax = ypos
            if target_xmin <= xpos <= target_xmax and target_ymin <= ypos <= target_ymax:
                if ymax > ovr_ymax:
                    ovr_ymax = ymax
                break
            if xpos > target_xmax or ypos < target_ymin:
                break
print(ovr_ymax)
