from dataclasses import dataclass
import sys
import os
from read import read
from pathlib import Path
import re

file = Path(os.path.abspath(__file__)).stem
input = read(file).splitlines()


@dataclass
class Blueprint():
    id: int
    ore: dict
    clay: dict
    obsidian: dict
    geode: dict


blueprints: list[Blueprint] = []
for line in input:
    numbers = [int(n) for n in re.findall(r'\d+', line)]
    blueprints.append(Blueprint(
        id=numbers[0],
        ore={'ore': numbers[1]},
        clay={'ore': numbers[2]},
        obsidian={'ore': numbers[3], 'clay': numbers[4]},
        geode={'ore': numbers[5], 'obsidian': numbers[6]}
    ))


def build(robots, resources, blueprint):
    for type in robots.keys():
        nrobots = robots.copy()
        nres = resources.copy()
        nrobots[type] += 1
        for nt, n in getattr(blueprint, type).items():
            nres[nt] -= n
        if all([n >= 0 for n in nres.values()]):
            yield nrobots, nres


def mine(robots, resources):
    nres = resources.copy()
    for type, n in robots.items():
        nres[type] += n
    return nres


def run(robots, resources, time, blueprint, best=0) -> int:
    if time == 0:
        return resources['geode']

    # Heuristik für max Geode
    if resources['geode'] + sum(range(time)) + time * robots['geode'] <= best:
        return 0

    # Roboter bauen
    for rob, res in build(robots, resources, blueprint):
        best = max(best, run(rob, mine(robots, res), time - 1, blueprint, best))

    # Keinen Roboter bauen
    best = max(best, run(robots, mine(robots, resources), time - 1, blueprint, best))
    print(best)

    return best


def part_1():
    quality_levels = 0
    for blueprint in blueprints:
        robots = {
            'geode': 0,
            'obsidian': 0,
            'clay': 0,
            'ore': 1
        }
        resources = {
            'geode': 0,
            'obsidian': 0,
            'clay': 0,
            'ore': 0
        }
        time = 24

        quality_levels += run(robots, resources, time, blueprint) * blueprint.id
        print(quality_levels)
    return quality_levels


def part_2():
    pass


print(globals()[f'part_{sys.argv[1]}']())
