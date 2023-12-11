file = open("input.txt").read().strip()
G = file.split('\n')
T = list(zip(*G))
row_len = len(G[0])
col_len = len(T[0])    

expanded_rows =  []
expanded_cols =  []

for c, col in enumerate(T):
    if ''.join(col) == '.'*col_len:
        expanded_cols.append(c)
for r, row in enumerate(G):
    if row == '.'*row_len:
        expanded_rows.append(r)



galaxies = []

for r, row in enumerate(G):
    row_str = ''.join(row)
    if '#' in row_str:
        c = 0
        while(1):
            c = row_str.find('#', c)
            if c == -1: break
            galaxies.append((r,c))
            c+=1

DIRS = [(-1,0), (1,0),(0,-1),(0,1)]

part1 = part2 = 0
from itertools import combinations
for comb in combinations(galaxies, 2):
    a,b = comb
    x,y = a
    u,v = b

    X = min(x,u)
    U = max(x,u)

    Y = min(y,v)
    V = max(y,v)

    expandX = list(filter(lambda x: x>=X and x <=U, expanded_rows))
    expandY = list(filter(lambda y: y>=Y and y <=V, expanded_cols))

    part1 += abs(x-u) + abs(y-v) + 1*len(expandX) + 1*len(expandY)
    part2 += abs(x-u) + abs(y-v) + 999999*len(expandX) + 999999*len(expandY)
     
    
print("part1: ", part1)
print("part2: ", part2)
    




