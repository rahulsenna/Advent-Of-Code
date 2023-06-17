#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef struct
{
	int cost;
    int damage;
    int armor;
} stats;

int main()
{
	int boss_hit_point, boss_damage, boss_armor, player_hit_points=100;
	string _;
	cin >> _ >> _ >> boss_hit_point >> _ >> boss_damage >> _ >> boss_armor;
    vector<stats> w = {{8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}};
    vector<stats> a = {{0, 0, 0}, {13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5}};
    vector<stats> r = {{0, 0, 0}, {25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, { 80, 0, 3 }};

	vector<int> build;
	int part_1 = INT_MAX;
	int part_2 = 0;
	
	for (auto &weapon: w)	
		for (auto &armor: a)
			for (auto &ring1: r)
				for (auto &ring2: r)
				{
                    int total_cost    = weapon.cost + armor.cost + ring1.cost + ring2.cost;
                    int player_damage = weapon.damage + ring1.damage + ring2.damage;
                    int player_armor  = armor.armor + ring1.armor + ring2.armor;

                    float aa = ceil(float(boss_hit_point) / float(max(1, player_damage - boss_armor)));
                    float bb = ceil(float(player_hit_points) / float(max(1, boss_damage - player_armor)));

                    if (aa <= bb)
						part_1 = min(total_cost, part_1);
					
					if (aa > bb)
						part_2 = max(total_cost, part_2);
                }
				
	
	std::cout << "part_1: " << part_1 << '\n';
	std::cout << "part_2: " << part_2 << '\n';
    
    return(0);
}
