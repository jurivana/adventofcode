import os
from math import ceil, prod


def read_packet(string, sub_packet=False):
    id = int(string[3:6], 2)
    pos = 6
    value = None
    if id == 4:
        keep_going = True
        literal = ''
        while (keep_going):
            keep_going = int(string[pos])
            literal += string[pos + 1:pos + 5]
            pos += 5
        value = int(literal, 2)
    else:
        length_type_id = int(string[pos])
        pos += 1
        values = []
        if length_type_id:
            sub_packets = int(string[pos:pos + 11], 2)
            pos += 11
            for _ in range(sub_packets):
                p, v = read_packet(string[pos:], True)
                pos += p
                values.append(v)
        else:
            total_length = int(string[pos:pos + 15], 2)
            pos += 15
            end = pos + total_length
            while pos < end:
                p, v = read_packet(string[pos:], True)
                pos += p
                values.append(v)
        if id == 0:
            value = sum(values)
        elif id == 1:
            value = prod(values)
        elif id == 2:
            value = min(values)
        elif id == 3:
            value = max(values)
        elif id == 5:
            value = int(values[0] > values[1])
        elif id == 6:
            value = int(values[0] < values[1])
        elif id == 7:
            value = int(values[0] == values[1])

    if not sub_packet:
        pos = ceil(pos / 8) * 8
    return (pos, value)


with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()[0]

bin_str = bin(int(input, 16))[2:].zfill(len(input) * 4)
_, value = read_packet(bin_str)
print(value)
