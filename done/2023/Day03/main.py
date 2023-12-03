file = open("input.txt").read().strip()
lines = file.split('\n')
from collections import defaultdict
from functools import reduce


mat = []
dirs = [(-1,-1),(1,1),(1,-1),(-1,1),(-1,0),(1,0),(0,-1),(0,1)]
for row, line in enumerate(lines):
    for idx, c in enumerate(line[::]):
        if not c.isdigit() and c != '.':
            for dir in dirs:
              mat.append((row+dir[0],idx+dir[1]))            
res1 = 0
possible_gear = defaultdict(list)

import re
for row, line in enumerate(lines):
    nums = re.findall(r'(\d+)',line )
    lf = 0
    for num in nums:
        idx = line.find(num,lf)
        lf = idx+len(num)
        for col in range(idx,idx+len(num)):
            if ((row,col)) in mat:
                res1 += int(num)
                gear_idx = int(mat.index((row,col))/8)
                possible_gear[gear_idx].append(int(num))
                break

gear_ratio = sum(map(lambda kv: reduce(lambda x, y: x * y, kv[1]) if len(kv[1]) > 1 else 0, possible_gear.items()))

print("part1: ", res1)
print("part2: ", gear_ratio)

