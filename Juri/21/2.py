RESULTS = {}


def take_turns(pos1, pos2, score1, score2):
    if score1 >= 21:
        return (1, 0)
    if score2 >= 21:
        return (0, 1)
    if (pos1, pos2, score1, score2) in RESULTS:
        return RESULTS[(pos1, pos2, score1, score2)]
    result = (0, 0)
    for d1 in [1, 2, 3]:
        for d2 in [1, 2, 3]:
            for d3 in [1, 2, 3]:
                npos1 = (pos1 + d1 + d2 + d3 - 1) % 10 + 1
                nscore1 = score1 + npos1

                won2, won1 = take_turns(pos2, npos1, score2, nscore1)
                result = (result[0] + won1, result[1] + won2)
    RESULTS[(pos1, pos2, score1, score2)] = result
    return result


print(max(take_turns(6, 4, 0, 0)))
