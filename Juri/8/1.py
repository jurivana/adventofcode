import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

sum = 0
for line in input:
    output = line.split('|')[1].split()
    for digit in output:
        if len(digit) in [2, 3, 4, 7]:
            sum += 1

print(sum)
