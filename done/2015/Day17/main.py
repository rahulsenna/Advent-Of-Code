import itertools

numbers = [11,30,47,31,32,36,3,1,5,3,32,36,15,11,46,26,28,1,19,3]

arrangements_count = 0
min_containers =0

# Generate all possible combinations of the numbers
for r in range(1, len(numbers) + 1):
    for combination in itertools.combinations(numbers, r):
        if sum(combination) == 150:            
            arrangements_count += 1
    if arrangements_count and not min_containers:
        min_containers = arrangements_count


print("min_containers: ", min_containers)
print("arrangements_count: ", arrangements_count)