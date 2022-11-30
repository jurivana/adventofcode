import os
from collections import Counter

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

[template, _, *lines] = input
rules = {}
for line in lines:
    pair, element = line.split(' -> ')
    rules[pair] = element

single_cnt = Counter({template[-1]: 1})
cnt = Counter()
for i in range(len(template) - 1):
    cnt[template[i] + template[i + 1]] += 1

for _ in range(40):
    temp = Counter()
    for pair, num in cnt.items():
        inserted = rules[pair]
        temp[pair[0] + inserted] += num
        temp[inserted + pair[1]] += num
    cnt = temp

for pair, num in cnt.items():
    single_cnt[pair[0]] += num

single_cnt_list = single_cnt.most_common()
print(single_cnt_list[0][1] - single_cnt_list[-1][1])
