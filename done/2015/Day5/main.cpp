#include <bits/stdc++.h>
#include <regex>

// https://adventofcode.com/2015/day/5
using namespace std;

int count_nice_words_pt2(vector<string> &words)
{
	int sum = 0;
	for (auto &word: words)
	{
        if (regex_search(word, regex("(\\w\\w).*\\1")) &&
            regex_search(word, regex("(\\w)\\w\\1")))
        {
			sum++;
		}
    }
    return sum;
}

int count_nice_words(vector<string> &words)
{
	int sum = 0;
	for (auto &word: words)
	{
        if (!regex_search(word, regex("(ab|cd|pq|xy)")) &&
            (regex_search(word, regex("(\\w)\\1")) &&
             regex_search(word, regex(".*[aeiou].*[aeiou].*[aeiou]"))))
        {
			sum++;
		}
    }
    return sum;
}


// ^(?!.*(\w)\1).*$

int main()
{
	fstream file("input.txt");
	vector<string> input = {istream_iterator<string>(file), {}};
	auto res = count_nice_words_pt2(input);
    return(0);
}