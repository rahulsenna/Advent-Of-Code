from collections import defaultdict, Counter
from functools import reduce

file = open("input.txt").read().strip()

deck = [line.split() for line in file.split('\n')]

part2_deck = []
part1_deck = []

for hand,bid in deck:
    counts = Counter(hand)
    hand1 = hand.replace('A','E').replace('K','D').replace('Q','C').replace('J','B').replace('T','A')
    joker_hand = hand.replace('A','E').replace('K','D').replace('Q','C').replace('J','1').replace('T','A')

    j_cnt = counts['J']
    c = list(reversed(sorted(counts.values())))
   
    j = 0
    if c == [5]:
        r = 501
    
    if c == [4,1]:
        r = 401
        if j_cnt:
            j = 100
    
    if c == [3,2]:
        r = 302
        if j_cnt:
            j  = 199

    if c == [3,1,1]:
        r = 301
        if j_cnt:
            j = 100    

    if c == [2,2,1]:
        r = 202
        if j_cnt == 1:
            j = 100
        elif j_cnt == 2:
            j = 199
            

    if c == [2,1,1,1]:
        r = 201
        if j_cnt:
            j = 100

    if c == [1,1,1,1,1]:
        r = 101
        if j_cnt:
            j = 100
            
    part1_deck.append((r, hand1, int(bid) ))
    part2_deck.append((r+j,joker_hand, int(bid) ))


h = sorted(part2_deck)
rank = 1
winnings_pt1 =  winnings_pt2 = 0
for _, hand,bid in sorted(part1_deck):
    winnings_pt1 +=  bid * rank
    rank +=1
rank = 1
for _, hand,bid in sorted(part2_deck):
    winnings_pt2 +=  bid * rank
    rank +=1        

print("part1: ", winnings_pt1)
print("part2: ", winnings_pt2)

