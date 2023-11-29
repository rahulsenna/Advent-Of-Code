#include <bits/stdc++.h>
using namespace std;


int main()
{
	// ifstream file("sample.txt");
	ifstream file("input.txt");
	
	vector<int>elves;
	int total = 0;
    for (string line; getline(file, line);)
		line.empty() ? elves.push_back(total), total=0 : total+=(stoi(line));
	
	sort(elves.rbegin(), elves.rend());
	cout << "part1: " << elves.front() << '\n';

	auto res2 = accumulate(elves.begin(), elves.begin()+3,0); // top 3
	std::cout << "part2: " << res2 << '\n';
	return(0);

}