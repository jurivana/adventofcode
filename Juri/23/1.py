from collections import deque

R1T = 11
R2T = 13
R3T = 15
R4T = 17
COSTS = {'A': 1, 'B': 10, 'C': 100, 'D': 1000}

NO_STOP = {2, 4, 6, 8}
TARGET = {'A': {11, 12}, 'B': {13, 14}, 'C': {15, 16}, 'D': {17, 18}}
TARGET_TOP = {'A': 11, 'B': 13, 'C': 15, 'D': 17}
START = '...........ADCDBBAC'


def move(state, a, b):
    t = list(state)
    t[a], t[b] = t[b], t[a]
    return ''.join(t)


def moves(state):
    for rt in (R1T, R2T, R3T, R4T):
        if state[rt] != '.' and state[rt + 1] == '.' and rt in TARGET[state[rt]]:
            yield move(state, rt, rt + 1), COSTS[state[rt]]

    for rt in (R1T, R2T, R3T, R4T):
        if (
            state[rt] == '.'
            and state[rt + 1] != '.'
            and rt not in TARGET[state[rt + 1]]
        ):
            yield move(state, rt, rt + 1), COSTS[state[rt + 1]]

    for rt in (R1T, R2T, R3T, R4T):
        if state[rt] == '.':
            continue
        if rt in TARGET[state[rt]] and state[rt + 1] in ('.', state[rt]):
            continue
        h0 = rt - 9
        for hall in range(h0 - 1, -1, -1):
            if hall in NO_STOP:
                continue
            if state[hall] != '.':
                break
            yield move(state, rt, hall), COSTS[state[rt]] * (h0 - hall + 1)
        for hall in range(h0 + 1, 11):
            if hall in NO_STOP:
                continue
            if state[hall] != '.':
                break
            yield move(state, rt, hall), COSTS[state[rt]] * (hall - h0 + 1)

    for hall in range(11):
        if state[hall] == '.':
            continue
        target = TARGET_TOP[state[hall]]
        if state[target] != '.' or (state[target + 1] not in ('.', state[hall])):
            continue
        h0 = target - 9
        if h0 > hall and all(state[h] == '.' for h in range(hall + 1, h0)):
            yield move(state, hall, target), COSTS[state[hall]] * (h0 - hall + 1)
        elif h0 < hall and all(state[h] == '.' for h in range(h0, hall)):
            yield move(state, hall, target), COSTS[state[hall]] * (hall - h0 + 1)


def solve(start: str) -> int:
    all_states = {start: (0, None)}
    queue = deque([start])
    while queue:
        state = queue.popleft()
        cost, _ = all_states[state]
        for next, next_cost in moves(state):
            if next in all_states and all_states[next][0] <= cost + next_cost:
                continue
            all_states[next] = (cost + next_cost, state)
            queue.append(next)

    st = '...........AABBCCDD'
    path = []
    while st:
        path.append((st, all_states[st][0]))
        st = all_states[st][1]
    return all_states['...........AABBCCDD'][0]


print(solve(START))
