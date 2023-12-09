#include <bits/stdc++.h>
using namespace std;


int main()
{
    ifstream file("input.txt");
    int64_t res2= 0, res1=0;
    for(string line; getline(file,line) && !line.empty();)
    {
        istringstream iss(line);
        vector<int64_t> first = {istream_iterator<int64_t>(iss), {}};
        vector<vector<int64_t>> H = {first};

        while(1)
        {
            vector<int64_t> T  = H.back();
            vector<int64_t> N;
            
            for (size_t i = 0; i < T.size()-1; ++i)
                N.emplace_back(T[i+1]-T[i]);
            H.emplace_back(N);

            if (all_of(N.begin(), N.end(), [](auto a) { return a==0;}))
            	break;
        }

        for (size_t i = H.size() - 1; i > 0; --i)
        {
            auto &u = H[i - 1];
            u.push_back(H[i].back() + u.back());
        }
        res1+= H.front().back();

    // Part 2
        vector<vector<int64_t>> H2 = {{first.rbegin(), first.rend()}};
        while (1)
        {
            vector<int64_t> T  = H2.back();
            vector<int64_t> N = {};
            
            for (size_t i = 0; i < T.size()-1; ++i)
                N.emplace_back(T[i]-T[i+1]);
            H2.emplace_back(N);

            if (all_of(N.begin(), N.end(), [](auto a) { return a==0;}))             
            	break;
        }
        for (size_t i = H2.size() - 1; i > 0; --i)
        {
            auto &u = H2[i-1];
            u.push_back(u.back() - H2[i].back());
        }

        res2+= H2.front().back();

    }

    printf("part1: %lli\n", res1);
    printf("part2: %lli\n", res2);
	return(0);
}