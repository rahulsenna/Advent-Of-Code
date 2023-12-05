#include <bits/stdc++.h>
using namespace std;


int main()
{
    ifstream file("input.txt");

    char _;
    int no, idx = 0,sum = 0;
    vector<int> cards(199,1);
    for(string line,card; getline(file,line); ++idx)
    {
        stringstream ss(line);
        ss >> card >> no >>_;
        vector<int> win_n = {istream_iterator<int>(ss), {}};;
        ss  = stringstream({line.begin()+(int)line.find('|')+1,line.end()});
        vector<int> nums = {istream_iterator<int>(ss), {}};
        sort(win_n.begin(), win_n.end());

        int won=0;
        for (const auto n : nums)
            if (binary_search(win_n.begin(), win_n.end(), n))
                won++;
        
        for (int i = idx + 1; i < (won+idx+1); ++i)
            cards[i] += cards[idx];
        

        sum += (int)pow(2,won-1);
    }
    auto sum2 = accumulate(cards.begin(), cards.end(), 0);

    printf("part1: %d\n", sum);
    printf("part2: %d\n", sum2);
	return(0);
}