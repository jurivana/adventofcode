import os


def get_rating(input, pos, type):
    if (len(input) == 1):
        return input[0]
    one_bits = 0
    for number in input:
        one_bits += int(number[pos])
    if one_bits == len(input) / 2:
        common = type
    else:
        common = abs(-(0 if one_bits > len(input) / 2 else 1) + type)
    return get_rating(list(filter(lambda number: int(number[pos]) == common, input)), pos + 1, type)


with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()
    oxygen = get_rating(input, 0, 1)
    co2 = get_rating(input, 0, 0)
    print(int(''.join(str(bit) for bit in oxygen), 2) * int(''.join(str(bit) for bit in co2), 2))
