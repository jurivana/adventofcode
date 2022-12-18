from dataclasses import dataclass
from functools import cache
import sys
import os
from typing import Dict
from read import read
from pathlib import Path
import re

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()


@dataclass(frozen=True)
class Valve():
    name: str
    flow_rate: int
    tunnels: list[str]

    def __hash__(self):
        return hash(self.name)


valves: Dict[str, Valve] = {}


for line in input:
    name = line[6:8]
    flow_rate = int(re.search(r'\d+', line).group(0))
    tunnels = re.findall(r'[A-Z]{2}', line.split('valve')[-1])
    valves[name] = Valve(name, flow_rate, tunnels)


@cache
def solve(minutes, valve: Valve, opened: frozenset[Valve], helpers, inital_minutes=None) -> tuple[int, frozenset[str]]:
    if not inital_minutes:
        inital_minutes = minutes

    if minutes <= 0:
        if helpers > 0:
            return solve(inital_minutes, valves['AA'], opened, helpers - 1, inital_minutes)
        return 0

    best = 0

    # Nicht öffnen
    for tunnel in valve.tunnels:
        best = max(solve(minutes - 1, valves[tunnel], opened, helpers, inital_minutes), best)

    # Öffnen
    if valve.name not in opened and valve.flow_rate > 0 and minutes > 0:
        now_opened = set(opened)
        now_opened.add(valve.name)
        minutes -= 1
        valve_rate = minutes * valve.flow_rate

        for tunnel in valve.tunnels:
            best = max(valve_rate + solve(minutes - 1, valves[tunnel], frozenset(now_opened), helpers, inital_minutes), best)

    return best


def part_1():
    return solve(30, valves['AA'], frozenset(), 0)


def part_2():
    return solve(26, valves['AA'], frozenset(), 1)


print(globals()[f'part_{sys.argv[1]}']())
