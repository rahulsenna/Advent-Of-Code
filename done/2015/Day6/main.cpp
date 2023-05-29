#include <bits/stdc++.h>
using namespace std;

// https://adventofcode.com/2015/day/6

int part_one(fstream &input)
{
	vector<bitset<1000>> grid(1000);
	string line; char comma; string through;
    int x1, y1, x2, y2;
	string inst;
    while(getline(input, line))
	{
		stringstream ss(line);
		ss >> inst;
		if (inst == "turn")
			ss >> inst;
		ss >> x1 >> comma >> y1 >> through >> x2 >> comma >> y2;

		for (int y=y1; y<=y2; ++y)
		{
			for (int x=x1; x<=x2; ++x)
			{
				if (inst == "toggle")
					grid[y].flip(size_t(x));
				
				if (inst == "off")
					grid[y].set(size_t(x), false);

				if (inst == "on")
					grid[y].set(size_t(x));
			}
			
		}
	}
	int total = 0;
	for (auto &e: grid)
	{
		total += e.count();
	}
	return(total);
}

int part_two(fstream &input)
{
	vector<vector<int>> grid(1000, vector<int>(1000));
	string line; char comma; string through;
    int x1, y1, x2, y2;
	string inst;
    while(getline(input, line))
	{
		stringstream ss(line);
		ss >> inst;
		if (inst == "turn")
			ss >> inst;
		ss >> x1 >> comma >> y1 >> through >> x2 >> comma >> y2;

		for (int y=y1; y<=y2; ++y)
		{
			for (int x=x1; x<=x2; ++x)
			{
				if (inst == "toggle")
					grid[y][x] +=2;
				
				if (inst == "off")
                {
                    if (grid[y][x] > 0)
	                    grid[y][x]--;
                }

                if (inst == "on")
					grid[y][x]++;
			}
			
		}
	}
	int total = 0;
	for (auto &e: grid)
	{
		auto sum = accumulate(e.begin(), e.end(), 0);
		total += sum;
	}
	return(total);
}

int main()
{

	fstream input("input.txt");
	// vector<string> input(istream_iterator<string>(file), {});
	
	auto res = part_two(input);
	return(0);

}