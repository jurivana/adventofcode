import os

DX = [-1, -1, -1, 0, 0, 0, 1, 1, 1]
DY = [-1, 0, 1, -1, 0, 1, -1, 0, 1]
CHAR_MAPPER = {'.': 0, '#': 1}

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    [algorithm, _, *input] = f.read().splitlines()

algorithm = [char for char in algorithm]

infin_char = '.'
for _ in range(50):
    X = len(input) + 6
    Y = len(input[0]) + 6
    output = [[None for _ in range(Y)] for _ in range(X)]
    for x in range(X):
        for y in range(Y):
            iea_string = []
            for d in range(9):
                nx = x + DX[d] - 3
                ny = y + DY[d] - 3
                char = input[nx][ny] if 0 <= nx < X - 6 and 0 <= ny < Y - 6 else infin_char
                iea_string.append(CHAR_MAPPER[char])
            iea_string = ''.join([str(char) for char in iea_string])
            output[x][y] = algorithm[int(iea_string, 2)]
    input = output
    infin_char = output[0][0]

print(sum([line.count('#') for line in output]))
