def create_adjacency_list(file_path):
    adjacency_list = {}

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                (from_city, _, to_city, _, distance) = line.split()
                distance = int(distance)

                if from_city not in adjacency_list:
                    adjacency_list[from_city] = []

                adjacency_list[from_city].append((to_city, distance))

                if to_city not in adjacency_list:
                    adjacency_list[to_city] = []

                adjacency_list[to_city].append((from_city, distance))

    return adjacency_list

def nearest_neighbor(adjacency_list, start):
    visited = set([start])
    path = [start]
    current_city = start

    while len(visited) < len(adjacency_list):
        min_distance = float('inf')
        nearest_city = None

        for neighbor, distance in adjacency_list[current_city]:
            if neighbor not in visited and distance < min_distance:
                min_distance = distance
                nearest_city = neighbor

        if nearest_city is None:
            break

        path.append(nearest_city)
        visited.add(nearest_city)
        current_city = nearest_city

    return path

import sys

def tsp(adjacency_list, start):
    n = len(adjacency_list)
    all_visited = (1 << n) - 1

    memo = {}
    def dp_mask(mask, pos):
        if mask == all_visited:
            return adjacency_list[pos][start]

        if (mask, pos) in memo:
            return memo[(mask, pos)]

        result = sys.maxsize
        for i in range(n):
            if (mask >> i) & 1 == 0:
                result = min(result, adjacency_list[pos][i] + dp_mask(mask | (1 << i), i))

        memo[(mask, pos)] = result
        return result

    return dp_mask(1 << start, start)




file_path = 'input.txt'
adjacency_list = create_adjacency_list(file_path)

start_city = 'Faerun'
shortest_distance = tsp(adjacency_list, start_city)

print(f"Shortest distance: {shortest_distance}")