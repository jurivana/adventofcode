import sys
import os
from read import read
from pathlib import Path

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()

def check_cycle(cycle, x):
    if cycle in [20, 60, 100, 140, 180, 220]:
        return cycle * x
    return 0


def part_1():
    cycle = 1
    x = 1
    signal_strengths = 0
    for line in input:
        instruction, *args = line.split()
        cycle += 1
        signal_strengths += check_cycle(cycle, x)

        if instruction == 'addx':
            cycle += 1
            x += int(args[0])
            signal_strengths += check_cycle(cycle, x)
    
    return signal_strengths
        

def crt_draw(cycle, x):
    return '#' if cycle % 40 in (x, x+1, x+2) else '.'


def part_2():
    cycle = 1
    x = 1
    crt = '#'
    for line in input:
        instruction, *args = line.split()
        cycle += 1
        crt += crt_draw(cycle, x)

        if instruction == 'addx':
            cycle += 1
            x += int(args[0])
            crt += crt_draw(cycle, x)
        
    for i in range(6):
        print(crt[i*40:i*40+40])



print(globals()[f'part_{sys.argv[1]}']())
