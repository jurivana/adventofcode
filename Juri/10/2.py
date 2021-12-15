import os

completion_score = {
    ')': 1,
    ']': 2,
    '}': 3,
    '>': 4
}
opening = {'(': ')', '[': ']', '{': '}', '<': '>'}

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

scores = []
for line in input:
    score = 0
    char_list = []
    for character in line:
        if character in opening:
            char_list.append(character)
        else:
            if opening[char_list.pop()] != character:
                char_list = []
                break
    while char_list:
        score = score * 5 + completion_score[opening[char_list.pop()]]
    if score:
        scores.append(score)

print(scores)
print(sorted(scores)[len(scores)//2])
