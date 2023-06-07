#include <bits/stdc++.h>
using namespace std;

int main()
{
    unordered_map<string, vector<int>> ingredients_props;
	vector<int> cal;
	string _; int capacity, durability, flavor, texture, calories;
    while (cin >> _ >> _ >> capacity >> _ >> _ >> durability >> _ >> _ >> flavor >> _ >> _ >> texture >> _ >> _ >> calories)
    {
		ingredients_props["capacity"].push_back(capacity);
		ingredients_props["durability"].push_back(durability);		
		ingredients_props["flavor"].push_back(flavor);		
		ingredients_props["texture"].push_back(texture);		
		cal.push_back(calories);		
	}

    int five_hundred_cals = 0, max_score = 0;

    for (int a = 1; a < 100; ++a)
    {
        for (int b = 1; b < 100; ++b)
        {
            for (int c = 1; c < 100; ++c)
            {
                int d = 100 - a - b - c;
                if (d >= 1 && d < 100)
                {
                    int total = 1;

                    for (auto &[_, prop] : ingredients_props)
                    {
                        int temp = (a * prop[0] + b * prop[1] + c * prop[2] + d * prop[3]);
                        if (temp < 0) temp = 0;
                        total *= temp;
                    }
                    if (total)
                    {
                        max_score = max(max_score, total);
                        if ((a * cal[0] + b * cal[1] + c * cal[2] + d * cal[3]) == 500)
                            five_hundred_cals = max(five_hundred_cals, total);
                    }
                }
            }
        }
        }

	std::cout << "part_one_res: " << max_score << '\n';
	std::cout << "part_two_res: " << five_hundred_cals << '\n';

    return 0;
}