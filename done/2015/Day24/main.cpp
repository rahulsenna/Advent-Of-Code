#include <bits/stdc++.h>
#include "../../../libs/combinations.h"
using namespace std;

int64_t get_best_entanglement(int groups)
{
	ifstream input("input.txt");
	vector<int> weights(istream_iterator<int>(input), {});
	int desired_weight = accumulate(weights.begin(), weights.end(), 0)/groups;

	int64_t best_entanglement = INT64_MAX;
	for (int i = 1; best_entanglement == INT64_MAX; ++i)
	{
		 COMBINATIONS combinations(weights, i);
		 while(combinations.has_next())
		 {
			auto &combination = combinations.next();
			int sum = accumulate(combination.begin(), combination.end(), 0);
			if (sum == desired_weight)
            {
                int64_t entaglement = accumulate(combination.begin(), combination.end(), 1LL, multiplies<int64_t>());
                best_entanglement = min(best_entanglement, entaglement);
            }
         }
	}
	return(best_entanglement);
}

int main()
{
	std::cout << "part_one: " << get_best_entanglement(3) << '\n';
	std::cout << "part_two: " << get_best_entanglement(4) << '\n';
 	return(0);
}