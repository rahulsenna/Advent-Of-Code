#include <bits/stdc++.h>
using namespace std;

bool check(string thing, int amt, unordered_map<string, int> &profile)
{
    if (thing == "cats:" || thing == "trees:")
        return amt > profile[thing];

    if (thing == "goldfish:" || thing == "pomeranians:")
        return amt < profile[thing];

	return amt == profile[thing];
}
// https://adventofcode.com/2015/day/16
int main()
{
    unordered_map<string, int> profile{{"children:", 3}, {"cats:", 7}, {"samoyeds:", 2}, {"pomeranians:", 3}, {"akitas:", 0}, {"vizslas:", 0}, {"goldfish:", 5}, {"trees:", 3}, {"cars:", 2}, {"perfumes:", 1}};
    string a,b,c, _;
	int x,y,z, idx;
    while (cin >> _ >> idx >> _ >> a >> x >> _ >> b >> y >> _ >> c >> z)
    {
		// if (profile[a] == x && profile[b] == y && profile[c] == z)  // part one

        vector<pair<string, int>> itmes({{a, x}, {b, y}, {c, z}});
        auto matched = accumulate(itmes.begin(), itmes.end(), 1, [&profile](auto acc, auto &e) { return acc*check(e.first, e.second, profile); });
        if (matched)
        {
            std::cout << "idx: " << idx << '\n';
			return 1;
        }
    }

    return(0);
}