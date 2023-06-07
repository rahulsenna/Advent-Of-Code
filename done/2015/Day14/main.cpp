#include <bits/stdc++.h>
using namespace std;

typedef struct
{
	int speed;
	int fly_range;
	int rest_required;
	int fly_time;
	int rest_time;
	int distance;
	int point;
} reindeer;

// https://adventofcode.com/2015/day/14

int main()
{
    unordered_map<string, reindeer> reindeers;
    string name, _;
	int speed, fly, rest;
	while(cin >> name >> _ >> _ >> speed >> _ >> _ >> fly >> _ >> _ >> _ >> _ >> _ >> _ >> rest >> _)
		reindeers[name] = {speed, fly, rest, 0, 0, 0, 0};
	

	for (size_t i = 0; i < 2503; ++i)
	{
		int max_dist = 0;
        for (auto &[_, deer] : reindeers)
        {
            if (deer.fly_time < deer.fly_range)
            {
				deer.fly_time++;
				deer.distance += deer.speed;
            } else 
			{
				if (++deer.rest_time >= deer.rest_required)
				{
					deer.rest_time = 0;
					deer.fly_time = 0;
				}
			}
            max_dist = max(deer.distance, max_dist);
        }

        for (auto &e : reindeers)
        {
            auto &s = e.second;
			if (s.distance == max_dist)
				s.point++;
        }
    }

    int max_dist = 0, max_points = 0;
    for (auto &[_, deer] : reindeers)
    {
        max_dist   = max(max_dist, deer.distance);
        max_points = max(max_points, deer.point);
    }

    cout << "max_dist: " << max_dist << '\n';
	cout << "max_points: " << max_points << '\n';

    return(0);
}