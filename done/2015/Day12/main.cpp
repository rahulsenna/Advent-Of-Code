#include <bits/stdc++.h>
#include <string>
using namespace std;

int part_one(string &input)
{
	smatch matches; regex pattern("(-*\\d+)");
	
    string::const_iterator searchStart(input.cbegin());
	int total = 0;
    while (regex_search(searchStart, input.cend(), matches, pattern))
    {
        total += stoi(matches[0].str());
        searchStart = matches.suffix().first;
    }
    return total;
}

int part_two_with_regex(string &input)
{
    regex pattern(R"(\{[^{}]*\})");
    while (input.find(":\"red") != string::npos)
    {
        string out;
        string::const_iterator it = input.cbegin(), end = input.cend();
        for (smatch match; regex_search(it, end, match, pattern); it = match[0].second)
        {
            out += match.prefix();
            string obj = match.str();
            if (obj.find(":\"red") == string::npos)
                out += to_string(part_one(obj));
        }
        out.append(it, end);
        input = out;
    }

    return(part_one(input));
}

int part_two_with_regex_V2(string &input)
{
    regex pattern(R"(\{[^{}]*\})");
    while (input.find(":\"red") != string::npos)
    {
        string result;
        auto it  = sregex_iterator(input.begin(), input.end(), pattern);
        size_t pos = 0;
        for (; it != sregex_iterator(); ++it)
        {
            const smatch &match = *it;
            result += match.prefix();

            string obj = match.str();
            if (obj.find(":\"red") == string::npos)
                result += to_string(part_one(obj));

            pos = match.position() + match.length();
        }

        result += input.substr(pos);
        input = result;
    }

    return(part_one(input));
}



int part_two_brace_counting(string &input)
{

    size_t red_pos = 0;
    while (input.find("red", red_pos+1) != string::npos)
    {
        red_pos = input.find("red", red_pos+1);
        size_t right_pos = red_pos, left_pos = red_pos;

        int square = -1, curly = -1;
        while (square < 0 && curly < 0)
        {
            auto c = &input[--left_pos];
            switch (*c)
            {
                case '{':  curly++; break;
                case '}':  curly--; break;
                case '[': square++; break;
                case ']': square--; break;
            }
        }
        if (square >= 0)
            continue;

        int closing_curly = -1;
        while (closing_curly < 0)
        {
            auto c = &input[++right_pos];
            if (*c == '{')
                closing_curly--;
            if (*c == '}')
                closing_curly++;
        }

        for (size_t i = left_pos; i <= right_pos; ++i)
            input[i] = ' ';
    }

    return part_one(input);
}


int main()
{
    // https://adventofcode.com/2015/day/12
	string input;
	cin >> input;	
	auto res = part_two_with_regex_V2  (input);
    cout << "res: " << res << '\n';
	return(0);
}