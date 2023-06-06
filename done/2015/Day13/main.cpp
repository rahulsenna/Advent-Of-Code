#include <bits/stdc++.h>
using namespace std;


int solve(unordered_map<string, int> &points_table, vector<string> &people)
{
	int max_points = 0;
	do
	{
        int total_points =  0;
        for (size_t i = 0; i < people.size(); ++i)
		{
            int a = points_table[people[i] + people[(i+1) % people.size()]];
            int b = points_table[people[(i+1) % people.size()] + people[i]];
            total_points += a+b;
        }

        max_points = max(max_points, total_points);
    } 
	while (next_permutation(people.begin(), people.end()));

	return max_points;
}


int main()
{
	// https://adventofcode.com/2015/day/13
	unordered_map<string, int> points_table;
	string current, next, temp, gain_lose;
	int points;
	set<string> people_set;

	while(cin >> current >> temp >> gain_lose >> points >> temp >> temp >> temp >> temp >> temp >> temp >> next)
	{
		if (gain_lose == "lose")
			points *= -1;
		next = next.substr(0,next.length()-1);
		people_set.insert(current);
        people_set.insert(next);

        points_table[current+next] = points;
	}
    vector<string> people(people_set.begin(), people_set.end());


	//------------------------------------------------------
    auto part_1_res = solve(points_table, people);
	//------------------------------------------------------
	// Insert self;
	for (auto &e: people)
	{
		points_table["me"+e] = 0;
		points_table[e+"me"] = 0;
	}
	people.emplace_back("me");

    auto part_2_res = solve(points_table, people);
	//------------------------------------------------------
	
	std::cout << "part_1_res: " << part_1_res << '\n';
	std::cout << "part_2_res: " << part_2_res << '\n';

    return(0);
}