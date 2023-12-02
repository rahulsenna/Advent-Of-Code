#include <bits/stdc++.h>
using namespace std;


int main()
{
    ifstream file("input.txt");

    char _;
    int id,count;
    int res1=0,res2=0;
    for (string line, label, color; getline(file, line);)
    {
        stringstream ss(line);
        ss >> label >> id >> _;
        vector<pair<string,int>> cubes; // part1
        unordered_map<string, int> max_cubes = {{"red",1},{"blue",1},{"green",1}}; // part2
        while(ss)
        {
            ss >> count >> color;
            if (color.back() == ',' || color.back() == ';')
                color.pop_back();

            cubes.push_back({color, count});       // part1
            if (max_cubes[color] < count)          // part2
            	max_cubes[color] = count;   
        }
        res2 += accumulate(max_cubes.begin(), max_cubes.end(), 1, [](int acc,auto &c) { return acc*c.second;});
        sort(cubes.begin(), cubes.end(), [](const auto &l, const auto &r) { return l.second > r.second; });
        bool is_possible = (cubes.front().second < 13) || (cubes.front().second == 13 && cubes.front().first != "red") || (cubes.front().second == 14 && cubes.front().first == "blue");
        if (is_possible)
            res1 += id;                
    }
    
    printf("part_1: %d\n", res1);
    printf("part_2: %d\n", res2);

    return(0);
}