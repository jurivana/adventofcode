from functools import cmp_to_key
import sys
import os
from read import read
from pathlib import Path
from itertools import zip_longest

file = Path(os.path.abspath(__file__)).stem
input = read(file)


def compare(left, right) -> int:
    for l, r in zip_longest(left, right):
        if l is None:
            return -1
        if r is None:
            return 1

        if isinstance(l, list) and isinstance(r, list):
            if (cmp := compare(l, r)) is not None:
                return cmp
        elif isinstance(l, int) and isinstance(r, int):
            if l - r != 0:
                return l - r
        else:
            l = [l] if not isinstance(l, list) else l
            r = [r] if not isinstance(r, list) else r
            if (cmp := compare(l, r)) is not None:
                return cmp


def part_1():
    roi = 0
    inp = input.split('\n\n')
    for i, pair in enumerate(inp):
        inp_left, inp_right = pair.splitlines()
        packet_left = eval(inp_left)
        packet_right = eval(inp_right)
        roi += i + 1 if compare(packet_left, packet_right) < 0 else 0
    return roi


def part_2():
    inp = [line for line in input.splitlines() if line]
    inp.extend(['[[2]]', '[[6]]'])
    packets = sorted([eval(packet_input) for packet_input in inp], key=cmp_to_key(compare))
    return (packets.index([[2]]) + 1) * (packets.index([[6]]) + 1)


print(globals()[f'part_{sys.argv[1]}']())
