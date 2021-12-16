import os
from collections import Counter

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

[template, _, *lines] = input
rules = {}
for line in lines:
    pair, element = line.split(' -> ')
    rules[pair] = element

for _ in range(10):
    temp = ''
    for i in range(len(template)):
        temp += template[i]
        if i + 1 < len(template):
            temp += rules[template[i] + template[i + 1]]
    template = temp

cnt = Counter(template).most_common()
print(cnt[0][1] - cnt[-1][1])
