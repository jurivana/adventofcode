import os
import itertools
from collections import defaultdict


with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().strip()


scanners = input.split('\n\n')
scans = []
for scan in scanners:
    beacons = []
    for line in scan.split('\n'):
        line = line.strip()
        if line.startswith('--'):
            continue
        x, y, z = [int(v) for v in line.split(',')]
        beacons.append((x, y, z))
    scans.append(beacons)


def adjust(point, d):
    ret = [point[0], point[1], point[2]]
    for i, p in enumerate(list(itertools.permutations([0, 1, 2]))):
        if d//8 == i:
            ret = [ret[p[0]], ret[p[1]], ret[p[2]]]

    if d % 2 == 1:
        ret[0] *= -1
    if (d//2) % 2 == 1:
        ret[1] *= -1
    if (d//4) % 2 == 1:
        ret[2] *= -1
    return ret


NUM_SCANS = len(scans)
FINAL = set(scans[0])
SCANNER_POINTS = [None for _ in range(NUM_SCANS)]
SCANNER_POINTS[0] = (0, 0, 0)

GOOD = set([0])
BAD = set([x for x in range(1, NUM_SCANS)])

B_ADJ = {}
for i in range(NUM_SCANS):
    for d in range(48):
        B_ADJ[(i, d)] = [adjust(p, d) for p in scans[i]]

while BAD:
    found = None
    for b in BAD:
        if found:
            continue
        for g in [0]:
            g_scan = [tuple([p[0]+SCANNER_POINTS[g][0], p[1]+SCANNER_POINTS[g][1], p[2]+SCANNER_POINTS[g][2]]) for p in FINAL]
            g_set = set(g_scan)
            for b_dir in range(48):
                b_scan = B_ADJ[(b, b_dir)]
                VOTE = defaultdict(int)
                for bi in range(len(scans[b])):
                    for gi in range(len(g_scan)):
                        dx = -b_scan[bi][0] + g_scan[gi][0]
                        dy = -b_scan[bi][1] + g_scan[gi][1]
                        dz = -b_scan[bi][2] + g_scan[gi][2]
                        VOTE[(dx, dy, dz)] += 1
                for (dx, dy, dz), val in VOTE.items():
                    if val >= 12:
                        SCANNER_POINTS[b] = (dx, dy, dz)
                        for p in b_scan:
                            FINAL.add(tuple([p[0] + dx, p[1]+dy, p[2]+dz]))
                        found = b
    BAD.remove(found)
    GOOD.add(found)
print(len(FINAL))
