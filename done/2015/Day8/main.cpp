#include <bits/stdc++.h>
using namespace std;

size_t part_one(vector<string> &lines)
{
    size_t chars = 0, in_memory = 0;

    for (auto &e: lines)
	{
		chars += e.length();
        e = regex_replace(e, regex("(\\\\\")|(\\\\\\\\)|(\\\\x..)"), "$");
		in_memory += e.length()-2;
	}

	 return(chars - in_memory);	
}

size_t part_two(vector<string> &lines)
{
    size_t chars = 0, encoded = 0;

    for (auto &e: lines)
	{
		chars += e.length();
		size_t q = count(e.begin(), e.end(), '"');
		size_t s = count(e.begin(), e.end(), '\\');

		encoded += e.length()+2+q+s;
	}

    return (encoded - chars);
}

int main()
{
	// https://adventofcode.com/2015/day/8
	
	ifstream file("input.txt");

	vector<string> lines(istream_iterator<string>(file), {});

	auto res = part_two(lines);
    std::cout << "res: " << res << '\n';

    return(0);
}