import sys
import os
from read import read
from pathlib import Path
from queue import LifoQueue
from collections import defaultdict
import re


file = Path(os.path.abspath(__file__)).stem
stack_input, procedure_input = read(file).split('\n\n')
stack_input = stack_input.splitlines()[-2::-1]
procedure_input = procedure_input.splitlines()


stacks = defaultdict(LifoQueue)
for stack in stack_input:
    for i in range(1, len(stack), 4):
        if stack[i].strip():
            stacks[i // 4 + 1].put(stack[i])


def part_1():
    for procedure in procedure_input:
        quantity, from_stack, to_stack = map(int, re.findall(r'\d+', procedure))
        for _ in range(quantity):
            item = stacks[from_stack].get()
            stacks[to_stack].put(item)

    return ''.join([stack.get() for stack in stacks.values()])


def part_2():
    for procedure in procedure_input:
        quantity, from_stack, to_stack = map(int, re.findall(r'\d+', procedure))
        items = []
        for _ in range(quantity):
            items.append(stacks[from_stack].get())
        for item in items[::-1]:
            stacks[to_stack].put(item)

    return ''.join([stack.get() for stack in stacks.values()])


print(globals()[f'part_{sys.argv[1]}']())
