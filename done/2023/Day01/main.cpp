#include <bits/stdc++.h>
using namespace std;

int main()
{
    // ifstream file("sample.txt");
    ifstream file("input.txt");

    int res1 = 0;
    for (string line; file >> line;)
    {
        line.erase(remove_if(line.begin(), line.end(), ::isalpha), line.end());
        res1 += stoi(string{line.front(), line.back()});
    }
    printf("part1: %d\n", res1);

    //----------------------------------------------------------
    //  part two
    file = ifstream("input.txt");
    int res2 = 0;
    unordered_map<string, string> num_map = {{"1", "one"}, {"2", "two"}, {"3", "three"}, {"4", "four"}, {"5", "five"}, {"6", "six"}, {"7", "seven"}, {"8", "eight"}, {"9", "nine"}};

    for (string line; file >> line;)
    {
        for (const auto &num : num_map)
        {
            size_t found = line.find(num.second);
            while (found != string::npos)
            {
                line.replace(found+1, 1, num.first);
                found = line.find(num.second, found+1);
            }
        }
        line.erase(remove_if(line.begin(), line.end(), ::isalpha), line.end());
        res2 += stoi(string{line.front(), line.back()});
    }

    printf("part2: %d\n", res2);
    return (0);
}