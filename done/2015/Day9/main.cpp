#include <bits/stdc++.h>
using namespace std;

int main()
{
	// Solving with Permutation method
	// https://adventofcode.com/2015/day/9

	fstream file("input.txt");
	string line;
	set<string> cities_set;
	unordered_map<string, int> distance;

    while (getline(file, line))
    {
        string       src, to, dest, eq;
        int          dist;
        stringstream ss(line);
        ss >> src >> to >> dest >> eq >> dist;

        cities_set.insert(src);
        cities_set.insert(dest);

        distance[src + dest] = dist;
        distance[dest + src] = dist;
    }
    vector<string> cities(cities_set.begin(), cities_set.end());

    int longest = 0, shortest = INT_MAX;

    do
    {
        int dist = 0;
        for (int i = 0; i < cities.size() - 1; ++i)
            dist += distance[cities[i] + cities[i + 1]];

        if (dist > longest)
            longest = dist;
        if (dist < shortest)
            shortest = dist;
    } while (next_permutation(cities.begin(), cities.end()));


    return(0);
}