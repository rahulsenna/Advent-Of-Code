#include <bits/stdc++.h>
using namespace std;

void part_one(vector<pair<string, string>> &molecules, string target_molecule)
{
	set<string> res;
    for (auto &[a, b] : molecules)
    {
        size_t found = INT_MAX;
        while (1)
        {
			string target = target_molecule;
            if (found == INT_MAX)
                found = target.find(a);
			else
                found = target.find(a, found+1);

            if (found == string::npos)
				break;

			target.replace(found, a.size(), b);
			res.insert(target);
        }
    }

	std::cout << "part one: " << res.size() << '\n';
}

void part_two(vector<pair<string, string>> &molecules, string target_molecule)
{
	// Using random shuffle to get lucky
	// https://www.reddit.com/r/adventofcode/comments/3xflz8/comment/cy4cu5b/
	string target = target_molecule;

    int part_2 = 0;
    while (target != "e")
	{
		string temp = target;

        for (auto &[a, b] : molecules)
        {
			auto pos = target.find(b);
			if (pos == string::npos)
				continue;
			
			target.replace(pos, b.size(), a);
			part_2++;
		}

		if (temp == target)
		{
			target = target_molecule;
			part_2 = 0;

            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(molecules.begin(), molecules.end(), default_random_engine(seed));
		}
	}
	std::cout << "part_two: " << part_2 << '\n';
}

int main()
{
	vector<pair<string, string>> molecules;
	string from, to, _;
	while(cin >> from >> _ >> to)	
        molecules.emplace_back(from, to);

	part_one(molecules, from);
	part_two(molecules, from);

    return(0);


}