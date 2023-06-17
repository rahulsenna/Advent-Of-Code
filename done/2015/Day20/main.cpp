#include <bits/stdc++.h>
using namespace std;


void part_1()
{
	vector<int> house(3400000, 0);
	for (size_t i = 1; i <= 3400000; ++i)
	{
		for (size_t j = i; j <= 3400000; j+=i)		
			house[j] += i*10;	
    }
	
	auto it = find_if(house.begin(), house.end(), [](auto e) { return e >= 34000000;});
	std::cout << "part_1: " << it-house.begin() << '\n';
}

void part_2()
{
    vector<int> house(3400000, 0);
    for (size_t i = 1; i <= 3400000; ++i)
    {
        for (size_t j = i, h = 0; h < 50 && j <= 3400000; j += i, h++)
            house[j] += i*11;	
    }
	
	auto it = find_if(house.begin(), house.end(), [](auto e) { return e >= 34000000;});
	std::cout << "part_2: " << it-house.begin() << '\n';
}

int main()
{
	part_1();
	part_2();
	return(0);
}
