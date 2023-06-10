#include <bits/stdc++.h>
using namespace std;

int count_adjacent_on(int x, int y, vector<vector<bool>> &grid)
{	
	int h = grid.size()-1;

    auto bottom = y == h ? 0 : grid[x][y + 1];
    auto top    = y == 0 ? 0 : grid[x][y - 1];
    auto left   = x == 0 ? 0 : grid[x - 1][y];
    auto right  = x == h ? 0 : grid[x + 1][y];

    auto top_right    = y == 0 || x == h ? 0 : grid[x + 1][y - 1];
    auto top_left     = y == 0 || x == 0 ? 0 : grid[x - 1][y - 1];
    auto bottom_right = y == h || x == h ? 0 : grid[x + 1][y + 1];
    auto bottom_left  = y == h || x == 0 ? 0 : grid[x - 1][y + 1];

	return(bottom + top + left + right + top_right + top_left + bottom_right + bottom_left);
}

int main()
{
	vector<vector<bool>> grid(100);
	string line; int idx = 0;
    while (cin >> line)
	{
		auto &row = grid[idx++];
		row.reserve(100);
		for (auto &c: line)
		{
			if (c=='.')
				row.emplace_back(false);
			else
				row.emplace_back(true);
		}
	}
#if PART_TWO 
		grid[0][0] = grid[99][99] = grid[0][99] = grid[99][0] = true;
#endif

    for (size_t i = 0; i < 100; ++i)
	{
		vector<vector<bool>> temp_grid = grid;

        for (size_t y = 0; y < 100; ++y)
        {
            for (size_t x = 0; x < 100; ++x)
            {
#if PART_TWO 
                if ((x == 0 && y == 0) || (x == 99 && y == 99) || (x == 0 && y == 99) || (x == 99 && y == 0))
                    continue;                
#endif
                int on = count_adjacent_on(x, y, grid);
				if (on == 3)
				{
                    temp_grid[x][y] =true;
					continue;
                }
                if (on == 2 && grid[x][y] == true)
					continue;
                
				temp_grid[x][y] = false;
            }
        }
		grid = temp_grid;
    }

	int on_lights = 0;
	for (auto &row: grid)
	{
		auto sum = accumulate(row.begin(), row.end(), 0);
		on_lights+= sum;
	}

	std::cout << "on_lights: " << on_lights << '\n';
    return(0);

}