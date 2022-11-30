import sys
import os


def read(day):
    with open(os.path.join(os.path.dirname(__file__), f'input/{day}'), "r") as f:
        return f.read()
