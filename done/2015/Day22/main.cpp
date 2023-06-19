/* 
	https://adventofcode.com/2015/day/22

	Recursive backtracking

	try all the cobinations recursivly
	upon win/loss undo_last_move(return) and try next move
	in the end return lowest mana_spent

	keep track of best_mana(lowes_mana_spent)

	Misile -> Misile -> Misile -> Misile -> Misile -> [LOST]
	Misile -> Misile -> Misile -> Misile -> Drain -> [LOST]
	Misile -> Misile -> Misile -> Misile -> Shield -> [LOST]
	...
	Misile -> Misile -> Misile -> Drain ->  Misile -> [LOST]
	Misile -> Misile -> Misile -> Drain ->  Drain -> [LOST]
	Misile -> Misile -> Drain -> Misile -> Misile -> [LOST]
	...

 */
#include <bits/stdc++.h>
using namespace std;

int boss_hp, boss_damage;
bool is_part_2 = false;

int simmulate(int player_hp, int boss_hp, int mana, int spent_mana, int shield, int poison, int recharge, bool is_player_turn)
{
	if (boss_hp <= 0)
		return spent_mana;
	
	if (player_hp <= 0)
		return INT_MAX;
	
	int armor = 0;
	if (shield > 0)
	{
		shield--;
		armor = 7;
	}
	if (poison > 0)
	{
		poison--;
        boss_hp -= 3;
    }
    if (recharge > 0)
    {
		recharge--;
        mana += 101;
    }

    if (is_player_turn)
	{
        if (mana < 53)
            return INT_MAX;
		if (is_part_2)
			player_hp--;

		// Missile
		int best_mana = simmulate(player_hp, boss_hp-4, mana-53, spent_mana+53, shield, poison, recharge, false);

		// Drain
		best_mana = min(best_mana, simmulate(player_hp+2, boss_hp-2, mana-73, spent_mana+73, shield, poison, recharge, false));

		// Shield
		if (shield ==0 && mana >= 113)
            best_mana = min(best_mana, simmulate(player_hp, boss_hp, mana-113, spent_mana+113, 6, poison, recharge, false));

        // Poison
		if (poison ==0 && mana >= 173)
            best_mana = min(best_mana, simmulate(player_hp, boss_hp, mana-173, spent_mana+173, shield, 6, recharge, false));

        // Recharge
		if (recharge ==0 && mana >= 229)
			best_mana = min(best_mana, simmulate(player_hp, boss_hp, mana-229, spent_mana+229, shield, poison, 5, false));

		return best_mana;
	} else
	{
		// Bosses Turn
		player_hp -= max(1, boss_damage - armor);
		return simmulate(player_hp, boss_hp, mana, spent_mana, shield, poison, recharge, true);
	}
}

int main()
{
	string _;
	cin >> _ >> _ >> boss_hp >> _ >> boss_damage;

	int player_hp = 50, mana = 500;	

	auto part_1 = simmulate(player_hp, boss_hp, mana, 0, 0, 0, 0, true);
	std::cout << "part_1: " << part_1 << '\n';
	
	is_part_2 = true;
	auto part_2 = simmulate(player_hp, boss_hp, mana, 0, 0, 0, 0, true);
	std::cout << "part_2: " << part_2 << '\n';

	return 0;
}