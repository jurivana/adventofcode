import os
from collections import defaultdict

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()

sum = 0
for line in input:
    signals, output = line.split('|')
    signals = signals.split()
    output = output.split()
    signals_by_len = defaultdict(list)
    digits = defaultdict(str)

    for signal in signals:
        signals_by_len[len(signal)].append(''.join(sorted(list(signal))))

    digits[signals_by_len[2][0]] = '1'
    digits[signals_by_len[3][0]] = '7'
    digits[signals_by_len[4][0]] = '4'
    digits[signals_by_len[7][0]] = '8'

    seven = list(signals_by_len[3][0])
    three = []
    for signal in signals_by_len[5][:]:
        if set(seven) <= set(signal):
            digits[signal] = '3'
            three = list(signal)
            signals_by_len[5].remove(signal)

    nine = []
    for signal in signals_by_len[6][:]:
        if set(three) <= set(signal):
            digits[signal] = '9'
            nine = list(signal)
            signals_by_len[6].remove(signal)

    topleft = (set(nine) - set(three)).pop()

    five = []
    for signal in signals_by_len[5]:
        if topleft in signal:
            digits[signal] = '5'
            five = list(signal)
        else:
            digits[signal] = '2'

    for signal in signals_by_len[6]:
        if set(five) <= set(signal):
            digits[signal] = '6'
        else:
            digits[signal] = '0'

    result = []
    for digit in output:
        result.append(digits[''.join(sorted(list(digit)))])
    sum += int(''.join(result))

print(sum)
