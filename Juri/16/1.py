import os
from math import ceil


def read_packet(string, sub_packet=False):
    global version_sum
    version = int(string[:3], 2)
    version_sum += version
    id = int(string[3:6], 2)
    pos = 6
    if id == 4:
        keep_going = True
        literal = ''
        while (keep_going):
            keep_going = int(string[pos])
            literal += string[pos + 1:pos + 5]
            pos += 5
        literal = int(literal, 2)
    else:
        length_type_id = int(string[pos])
        pos += 1
        if length_type_id:
            sub_packets = int(string[pos:pos + 11], 2)
            pos += 11
            for _ in range(sub_packets):
                pos += read_packet(string[pos:], True)
        else:
            total_length = int(string[pos:pos + 15], 2)
            pos += 15
            end = pos + total_length
            while pos < end:
                pos += read_packet(string[pos:], True)

    if not sub_packet:
        pos = ceil(pos / 8) * 8
    return pos


with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()[0]

bin_str = bin(int(input, 16))[2:].zfill(len(input) * 4)
version_sum = 0
pos = 0
while (pos < len(bin_str)):
    pos += read_packet(bin_str[pos:])

print(version_sum)
