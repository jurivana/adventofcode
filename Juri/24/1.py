import os
from typing import Union

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()


class ALU:
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
    digits = [int(d) for d in model_num]
    for i in range(len(digits) - 1, 0, -1):
        digits[i] -= 1
        if digits[i] == 0:
            digits[i] = 9
        else:
            break
    return ''.join([str(d) for d in digits])


model_num = '99999999999999'
while True:
    print(model_num)
    alu = ALU()
    digits = [int(d) for d in model_num]
    for line in input:
        [instr, *args] = line.split()
        if instr == 'inp':
            args.append(digits.pop(0))
        alu.exec(instr, *args)
    if alu.vars['z'] == 0:
        print(model_num)
        break
    model_num = decr_model_num(model_num)
