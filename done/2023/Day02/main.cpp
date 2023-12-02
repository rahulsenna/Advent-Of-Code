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
        unordered_map<string, int> max_cubes = {{"red",1},{"blue",1},{"green",1}};
        while(ss)
        {
            ss >> count >> color;
            if (color.back() == ',' || color.back() == ';')
                color.pop_back();
            if (max_cubes[color] < count)
            	max_cubes[color] = count;   
        }
        res2 += accumulate(max_cubes.begin(), max_cubes.end(), 1, [](int acc,auto &c) { return acc*c.second;});
        if ((max_cubes["red"] < 13) && (max_cubes["green"] < 14) && (max_cubes["blue"] < 15))
            res1 += id;      
    }
    
    printf("part_1: %d\n", res1);
    printf("part_2: %d\n", res2);

    return(0);
}