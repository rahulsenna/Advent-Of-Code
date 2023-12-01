import re
file = open("input.txt")
lines = file.readlines()

coords_one_sum = 0
for line in lines:
    m = re.findall(r'\d',line)
    if m:
        coords_one_sum += int(f'{m[0]}{m[-1]}')

print("part1: ", coords_one_sum)

#------------------------------------------------------
# part two
nums = {'one':1,'two':2,'three':3,'four':4,'five':5,'six':6,'seven':7,'eight':8,'nine':9,'zero':0}
num = [i for i in nums.keys() ]
n_r = [i[::-1] for i in nums.keys() ]

first_reg= fr'\d|{num[0]}|{num[1]}|{num[2]}|{num[3]}|{num[4]}|{num[5]}|{num[6]}|{num[7]}|{num[8]}|{num[9]}'
last_reg= fr'\d|{n_r[0]}|{n_r[1]}|{n_r[2]}|{n_r[3]}|{n_r[4]}|{n_r[5]}|{n_r[6]}|{n_r[7]}|{n_r[8]}|{n_r[9]}'
 
coords_two_sum = 0

for line in lines:
    if not re.findall(first_reg,line): break

    first = re.findall(first_reg,line)[0]
    last = re.findall(last_reg,line[::-1])[0][::-1]

    first_i = first if first.isdigit() else nums[first]
    last_i =  last if last.isdigit() else nums[last]
    
    coords_two_sum += int(f'{first_i}{last_i}')

print("part2: ", coords_two_sum)
