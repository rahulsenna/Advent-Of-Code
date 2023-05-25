#include <bits/stdc++.h>

using namespace std;

// https://adventofcode.com/2015/day/2

int wrapping_paper_size(vector<int> dims)
{
	int w = dims[0];
	int h = dims[1];
	int l = dims[2];

    vector<int> aa = {w * h, l * h, w * l};

    auto min = min_element(aa.begin(), aa.end());

	int total = 0;

	for (auto &e: aa)
	{
		total += e*2;
	}
	total += *min;

	return(total);
}

int ribbon_size(vector<int> dims)
{
	int bow = accumulate(dims.begin(), dims.end(), 1, multiplies<int>());

	sort(dims.begin(), dims.end());

	int total = 0;

	for (size_t i = 0; i < 2; ++i)
	{
		 total += dims[i]*2;
	}
	return(total+bow);
}

int main()
{	

	int total_wrapping_paper = 0;
	int total_ribbon = 0;

	ifstream file( "input.txt" );
	string line;
	while (getline(file, line))
	{
		replace(line.begin(), line.end(), 'x', ' ');
		stringstream ss(line);
		vector<int> dims(istream_iterator<int>(ss), {});
		total_wrapping_paper += wrapping_paper_size(dims);
	}

	file = ifstream( "input.txt" );
	while (getline(file, line))
	{
		vector<int> dims;
		stringstream ss(line);
		string segment;
        while (getline(ss, segment, 'x'))
        {
            dims.push_back(stoi(segment));
        }
        total_ribbon += ribbon_size(dims);
	}

	cout << "total_wrapping_paper: " << total_wrapping_paper << '\n';
	cout << "total_ribbon: " << total_ribbon << '\n';
	

	/* 
	std::ifstream file( "input.txt" );
	std::stringstream buffer;
    buffer << file.rdbuf();
	while (buffer)
	{
		string dim_str;
		buffer >> dim_str;
		replace(dim_str.begin(), dim_str.end(), 'x', ' ');
		stringstream ss(dim_str);

		vector<int> dims(istream_iterator<int>(ss), {});
		res += total_wrapping_paper(dims);
    } 
	*/


	return(0);
}