#include <bits/stdc++.h>
using namespace std;


bool sort_alphabetically(const pair<string, string> &a, const pair<string, string> &b)
{
    if (a.first.length() < b.first.length())
        return true;
    else if (a.first.length() > b.first.length())
        return false;
    else
        return a.first < b.first;
}

int iterative_method(unordered_map<string, string> &commands, string key)
{
	vector<pair<string, string>> instructions = {commands.begin(), commands.end()};
	sort(instructions.begin(), instructions.end(), sort_alphabetically);
	auto a = *instructions.begin();
	instructions.erase(instructions.begin());
    instructions.push_back(a);

	unordered_map<string, int> computed;
	for (auto &e: instructions)
	{	
		string command = e.second;

        if (regex_match(command, regex("^\\d+$")))
        {
            computed[e.first] = stoi(command);
			continue;
        }
        if (regex_match(command, regex("^\\w+$")))
        {
			computed[e.first] = computed[command];
			continue;
        }
        smatch sm;

        if (regex_match(command, sm, regex("^NOT (\\w+)$")))
        {
			string a = sm[1].str();
            computed[e.first] = 0xffff & ~computed[a];
			continue;
        }

        if (regex_match(command, sm, regex("^(.+) (\\w+) (.+)$")))
        {
            string left  = sm[1].str();
            string op    = sm[2].str();
            string right = sm[3].str();
            int    a, b;
			if (regex_match(left, sm, regex("^\\d+$")))
				a = stoi(left);
			else
                a = computed[left];

            if (regex_match(right, sm, regex("^\\d+$")))
                b = stoi(right);
            else
                b = computed[right];

            if (op == "AND")
                computed[e.first] = a & b;
            if (op == "OR")
                computed[e.first] = a | b;
            if (op == "RSHIFT")
                computed[e.first] = a >> b;
            if (op == "LSHIFT")
                computed[e.first] = a << b;
            continue;
        }
    }

	return computed[key];
}



int recursive_method(unordered_map<string, string> &map,  string key)
{
	static unordered_map<string, int> solved;
    string command = map[key];

	if (solved.find(key) != solved.end())
		return solved[key];
	
	if (regex_match(key, regex("^\\d+$")))
		return stoi(key);
	
	if (regex_match(command, regex("^\\d+$")))
    {
		solved[key] = stoi(command);
        return stoi(command);
    }

    if (regex_match(command, regex("^\\w+$")))
		return recursive_method(map,  command);
	
	smatch sm;
	if (regex_match(command, sm,  regex("^NOT (\\w+)$")))
	{
		string a = sm[1].str();
        int v = recursive_method(map, a);

        solved[key] = 0xffff & ~v;
        return 0xffff & ~v;
	}
	if (regex_match(command, sm, regex("^(.+) (\\w+) (.+)$")))
	{
		string left = sm[1].str();
        string op = sm[2].str();
        string right = sm[3].str();
		int a = recursive_method(map, left);
		int b = recursive_method(map, right);
		
		if (op == "AND")
        {
            solved[key] = a & b;
			return a & b;
        }
        if (op == "OR")
        {
            solved[key] = a | b;
			return a | b;
        }
        if (op == "RSHIFT")
        {
            solved[key] = a >> b;
			return a >> b;
        }
        if (op == "LSHIFT")
        {
            solved[key] = a << b;
			return a << b;
        }
    }
	return 0;
}

// https://adventofcode.com/2015/day/7

int main()
{
	fstream file("input.txt");

	unordered_map<string, string> commands;
	string line;
	while (getline(file, line))
	{
		size_t pos = line.find("->");
		commands[line.substr(pos+3)] = line.substr(0, pos-1);
	}

    auto res_ittr = iterative_method(commands, "a");

    auto res_rec  = recursive_method(commands, "a");

    return(0);
}