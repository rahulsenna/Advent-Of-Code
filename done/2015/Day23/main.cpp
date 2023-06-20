#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> code;
	string line;
	ifstream file("input.txt");

	while(getline(file, line))
		code.emplace_back(line);
    unordered_map<string, long long> regs = {{"a", 0}, {"b", 0}};

    for (int pc = 0; pc < code.size();)
    {
		line = code[pc];
		smatch sm;

		if (regex_match(line, sm, regex("(ji(?:o|e)) (\\w), ([+-]\\d+)")))
        {
            if (sm[1].str() == "jio")
			{
				if (regs[sm[2].str()] == 1)
					pc += stoi(sm[3].str());
				else
					pc++;
			} else
			{
				if (regs[sm[2].str()] % 2 == 0)
					pc += stoi(sm[3].str());
				else
					pc++;
			}
			continue;
        }

		if (regex_match(line, sm, regex("jmp ([+-]\\d+)")))
        {
            pc += stoi(sm[1].str());
			continue;
        }

		if (regex_match(line, sm, regex("inc (\\w)")))
			regs[sm[1].str()]++;

		if (regex_match(line, sm, regex("hlf (\\w)")))
			regs[sm[1].str()] /= 2;

		if (regex_match(line, sm, regex("tpl (\\w)")))
			regs[sm[1].str()] *=3;
		pc++;
	}

	std::cout << "b: " << regs["b"] << '\n';
	return(0);
}