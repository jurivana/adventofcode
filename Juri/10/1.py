import os

error_score = {
    ')': 3,
    ']': 57,
    '}': 1197,
    '>': 25137
}
opening = {'(': ')', '[': ']', '{': '}', '<': '>'}

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

score = 0
for line in input:
    char_list = []
    for character in line:
        if character in opening:
            char_list.append(character)
        else:
            if opening[char_list.pop()] != character:
                score += error_score[character]
                break
print(score)
