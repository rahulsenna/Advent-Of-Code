#include <bits/stdc++.h>
using namespace std;


int main()
{
	unordered_map<string, int> map1 = {
		{"AX", 4}, //draw
		{"BY", 5},
		{"CZ", 6}, 
		{"BX", 1}, // lose
		{"CY", 2},
		{"AZ", 3}, 
		{"CX", 7}, // win
		{"AY", 8}, 
		{"BZ", 9},
	};	
	unordered_map<string, int> map2 = {
		{"AX", 3}, // need to lose
		{"BX", 1},
		{"CX", 2}, 
		{"AY", 4}, // need to draw 
		{"BY", 5},
		{"CY", 6},
		{"AZ", 8}, // need to win 
		{"BZ", 9},
		{"CZ", 7},
};
	// ifstream file("sample.txt");
	ifstream file("input.txt");

	int res1=0,res2=0;
	for (char me,opp; file >> opp >> me; )
	{
		res1 += map1[{opp,me}];
		res2 += map2[{opp,me}];
	}

	std::cout << "part1:: " << res1 << '\n';
	std::cout << "part2:: " << res2 << '\n';

	return(0);

}