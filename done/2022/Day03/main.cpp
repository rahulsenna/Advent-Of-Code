#include <bits/stdc++.h>
using namespace std;


int main()
{
    ifstream file("input.txt");
    int sum = 0;    
    for(string line; file >> line;)
    {
        auto half_sz = line.size()/2;
        auto first_half = line.substr(0,half_sz);
        auto second_half = line.substr(half_sz,half_sz);
        string visited = {};
        for (auto &c: first_half)
        {
            if (second_half.find(c) != -1 && visited.find(c) == -1)
            {
                visited += c;
                int t = c - 96;
                if (isupper(c)) t += 58;               
                sum += t;
            }
        }
    }

    int sum2 = 0;
	file = ifstream("input.txt");
    for(string line1,line2,line3; file >> line1 >>line2 >>line3;)
    {
        string visited = {};
        for (auto &c: line1)
        {
            if (line2.find(c) != -1 && line3.find(c) != -1 && visited.find(c) == -1)
            {
                visited += c;
                int t = c - 96;
                if (isupper(c)) t += 58;               
                sum2 += t;
            }       
        }
    }
    printf("part1: %d\n", sum);
    printf("part2: %d\n", sum2);

	return(0);
}