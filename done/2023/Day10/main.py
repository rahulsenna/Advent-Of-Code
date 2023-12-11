from collections import deque

file = open("input.txt").read().strip()
lines = file.split('\n')

G = [ list(line) for line in lines]
rows = len(G)
cols = len(G[0])

dirs = {'down':(1,0), 'up':(-1,0),'left': (0,-1), 'right': (0,1)}
to_possibles = {'up':['|', '7', 'F'], 'down':['|', 'J', 'L'],'left': ['-', 'L', 'F'], 'right': ['-', 'J', '7']}
from_possibles = {'down':['|', '7', 'F'], 'up':['|', 'J', 'L'],'right': ['-', 'L', 'F'], 'left': ['-', 'J', '7']}
start = ()
visited = set()
P = deque()
for r in range(len(G)):
    for c in range(len(G[0])):
        p = G[r][c]
        if p == 'S':
            start = (r,c)
            P.append((0,(r,c),0))
            visited.add((r,c))
            break
possible_S = {'-', 'J', '7','L', 'F','|'}
part1 = 0
while(len(P)):
    pos = P.popleft()
    for dir_name,coord in dirs.items():
        if pos[2] != 0:
           if not pos[2] in from_possibles[dir_name]:
               continue
        r1,c1 = coord
        r2,c2 = pos[1]
        r,c = r1+r2,c1+c2

        p = G[r][c]
        if p == '.':
            continue

        if (r,c) in visited:
            if p == 'S':
                possible_S &= set(to_possibles[dir_name])
            continue

        if r >= rows or c >= cols:
            continue
        if r < 0 or c < 0:
            continue

        if p in to_possibles[dir_name]:
            P.append((pos[0]+1,(r,c),p))
            visited.add((r,c))
            part1 = pos[0]+1
            

(S,) = possible_S
G[start[0]][start[1]] = S
print("part1: ", part1)

for r, row in enumerate(G):
    for c, col in enumerate(row):
        if (r,c) not in visited:
            G[r][c] = '.'


outside = set()

for r, row in enumerate(G):
    within = False
    up = None
    for c, ch in enumerate(row):
        if ch == "|":
            assert up is None
            within = not within
        elif ch == "-":
            assert up is not None
        elif ch in "LF":
            assert up is None
            up = ch == "L"
        elif ch in "7J":
            assert up is not None
            if ch != ("J" if up else "7"):
                within = not within
            up = None
        elif ch == ".":
            pass
        if not within:
            outside.add((r, c))
part2 = len(G) * len(G[0]) - len(outside | set(visited))            
print("part2: ", part2)

