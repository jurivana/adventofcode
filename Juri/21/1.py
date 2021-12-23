pos = [6, 4]
score = [0, 0]
die = 1

t = 0
won = False
while not won:
    for i in range(2):
        pos[i] = (pos[i] + 3 * die + 2) % 10 + 1
        score[i] += pos[i]
        die = (die + 2) % 100 + 1
        t += 3
        if score[i] >= 1000:
            print(score[1-i] * t)
            won = True
            break
