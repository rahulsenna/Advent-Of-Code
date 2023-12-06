#include <bits/stdc++.h>
using namespace std;


int main()
{
	ifstream file("input.txt");
    vector<int> times, dists;
    for (string line,label; getline(file, line), !line.empty();)
    {
        istringstream iss(line); iss >> label;
        vector<int>& container = (label == "Time:") ? times : dists;
        container = {istream_iterator<int>(iss), {}};
    }

    int res1 = 1;
    for (size_t idx = 0; idx < times.size(); ++idx)
    {
        auto time = times[idx];
        int w = 0;
        for (size_t t = 0; t <= time; ++t)
            if (t *(time -t ) > dists[idx])
            	w++;
        res1 *=w;
    }

    uint64_t big_time = stoull(accumulate(times.begin(), times.end(), string{}, [](auto& a, auto b) { return a + to_string(b); }));
    uint64_t big_dist = stoull(accumulate(dists.begin(), dists.end(), string{}, [](auto& a, auto b) { return a + to_string(b); }));

    uint64_t res2 = 0;
    for (size_t t = 0; t <= big_time; ++t)
        if ((t * (big_time - t)) >= big_dist)        
            res2++;

    printf("part2: %llu\n", res2);
    printf("part1: %d\n", res1);

	return(0);
}