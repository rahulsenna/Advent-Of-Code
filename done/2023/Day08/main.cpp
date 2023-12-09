#include <bits/stdc++.h>

using namespace std;


int main()
{
	ifstream file("input.txt");
    string line;
    char _;
    getline(file,line);
    stringstream ss(line);
    vector<char> instructionC = {istream_iterator<char>(ss), {}};
    vector<int>  instruction(instructionC.size(), 0);
    transform(instructionC.begin(), instructionC.end(), instruction.begin(), [](char &c) {return (c == 'L')? 0:1 ;});

    
    getline(file, line); //Blank line

    unordered_map<string,pair<string,string>> MAP;


    for(string a,b,c;getline(file,line) && !line.empty();)
    {
        istringstream iss(line);
        iss >> a >> _ >> _ >> b >> c;
        b.pop_back();c.pop_back(); // removing a comma and a closing bracket
        MAP[a] = {b,c};
    }


    size_t idx = 0, steps = 0;
    string name = "AAA";

    while(name != "ZZZ")
    {        
        name = instruction[idx++]? MAP[name].second : MAP[name].first;
        steps += 1;
        idx %= instruction.size();
    }
    printf("part1: %llu\n", steps);
    

    vector<string> KEYS;
    transform(MAP.begin(), MAP.end(), std::back_inserter(KEYS), [](const auto& pair) { return pair.first; });

    vector<string> pos;
    copy_if(KEYS.begin(), KEYS.end(), back_inserter(pos), [](auto &e) {return e.back() == 'A' ? 1: 0;});
    
    idx = 0, steps = 0;
    unordered_map<size_t,size_t> cycle;
    while(pos.size() != cycle.size())
    {
        size_t right = instruction[idx++];
        idx %= instruction.size();
        steps++;
        {
            for (size_t i = 0; i < pos.size(); ++i)
            {
                auto &p = pos[i];
                p = right ? MAP[p].second : MAP[p].first;
                if (p.back() == 'Z')
                    cycle[i] = steps;
            }
        }
    }

    size_t res2 = accumulate(cycle.begin(), cycle.end(), 1LL, [](size_t acc, auto b) { return lcm(acc, b.second); });

    printf("part2: %llu\n", res2);
	return(0);
}