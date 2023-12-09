from collections import defaultdict, Counter
from functools import reduce

file = open("input.txt").read().strip()

instruction, network = file.split('\n\n')

network = network.replace('(','').replace(')','')
network = network.split('\n')
network = [m.split(' = ') for m in network]

MAP = {}

for m,n in network:
    MAP[m] = tuple(n.split(', '))
    
instruction = list(map(lambda x: 0 if x=='L' else  1, list(instruction)))


idx = 0
name = "AAA"
ans1 = 0
while(name != 'ZZZ'):
    inst = instruction[idx]
    
    name = MAP[name][inst]
    idx += 1
    ans1 += 1
    idx %= len(instruction)

print("part1: ", ans1)

positions = list(filter(lambda x: x.endswith('Z'), MAP.keys()))
cycles = {}
idx = 0
steps = 0

while(len(positions) !=  len(cycles)):
    direction = instruction[idx]
    curr = []
    steps += 1
    for i,p in enumerate(positions):
        w = MAP[p][direction]
        curr.append(w)
        if w.endswith('Z'):
            cycles[i] = steps
    positions = curr
    
    idx += 1
    idx %= len(instruction)

from math import gcd
res2 = reduce(lambda x, y: x * y // gcd(x, y), list(cycles.values()))

print("ans2: ", res2)
