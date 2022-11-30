import os

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    numbers, _, *input = f.read().splitlines()

numbers = numbers.split(',')
boards = []
def init_board():
    return {
        'board': [],
        'row': [0 for _ in range(5)],
        'col': [0 for _ in range(5)]
    }
curr_board = init_board()
for line in input:
    if not line:
        continue
    curr_board['board'].extend(line.split())
    if len(curr_board['board']) == 25:
        boards.append(curr_board)
        curr_board = init_board()
marked = []
for number in numbers:
    marked.append(number)
    for board in boards:
        try:
            index = board['board'].index(number)
            row = int(index / 5)
            board['row'][row] += 1
            col = index % 5
            board['col'][col] += 1
            if board['row'][row] == 5 or board['col'][col] == 5:
                print(sum([int(x) for x in filter(lambda x: x not in marked, board['board'])]) * int(number))
                break
        except:
            continue
    else:
        continue
    break