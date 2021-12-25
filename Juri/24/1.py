import os
from typing import Union

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()


stack = []
model_number = [None for _ in range(14)]
for i in range(14):
    check = int(input[i * 18 + 5].split()[2])
    offset = int(input[i * 18 + 15].split()[2])
    if check > 0:
        stack.append((i, offset))
    else:
        idx, val = stack.pop()
        if val + check > 0:
            model_number[i] = 9
            model_number[idx] = 9 - val - check
        else:
            model_number[idx] = 9
            model_number[i] = 9 + val + check
print(''.join([str(d) for d in model_number]))


"""Everything below this line is useless."""


class ALU:
    """
    Useless class.
    """

    def __init__(self):
        self.vars = {'w': 0, 'x': 0, 'y': 0, 'z': 0}
        self.names = {'w', 'x', 'y', 'z'}

    def get_value(self, a: Union[str, int]) -> int:
        try:
            a = int(a)
        except ValueError:
            a = self.vars[a]
        return a

    def inp(self, a: str, val: int):
        self.vars[a] = val

    def add(self, a: str, b: Union[str, int]):
        self.vars[a] += self.get_value(b)

    def mul(self, a: str, b: Union[str, int]):
        self.vars[a] *= self.get_value(b)

    def div(self, a: str, b: Union[str, int]):
        self.vars[a] = int(self.vars[a] / self.get_value(b))

    def mod(self, a: str, b: Union[str, int]):
        self.vars[a] %= self.get_value(b)

    def eql(self, a: str, b: Union[str, int]):
        self.vars[a] = 1 if self.vars[a] == self.get_value(b) else 0

    def exec(self, instr: str, *args):
        getattr(self, instr)(*args)


def decr_model_num(model_num: str):
    """
    Useless function.
    """
    digits = [int(d) for d in model_num]
    for i in range(len(digits) - 1, 0, -1):
        digits[i] -= 1
        if digits[i] == 0:
            digits[i] = 9

        else:
            break
    return ''.join([str(d) for d in digits])


"""
Slightly too slow.
"""
# model_num = '99999999999999'
# while True:
#     alu = ALU()
#     digits = [int(d) for d in model_num]
#     for line in input:
#         [instr, *args] = line.split()
#         if instr == 'inp':
#             args.append(digits.pop(0))
#         alu.exec(instr, *args)
#     if alu.vars['z'] == 0:
#         print(model_num)
#         break
#     model_num = decr_model_num(model_num)
