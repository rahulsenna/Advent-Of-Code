#include <bits/stdc++.h>
using namespace std;


int main()
{
    string input = "1321131112";
    string next_digits = "";
    for (size_t i = 0; i < 50; ++i)
    {
        int idx = 0;
        while (idx < input.length())
        {
            char c          = input[idx];
            int  char_count = 0;
            char next_char  = c;
            while (next_char == c)
            {
                next_char = input[++idx];
                char_count++;
            }

            next_digits += to_string(char_count) + c;
        }
        input = next_digits;
        next_digits = "";
        
    }


    std::cout << "input.length(): " << input.length() << '\n';
	return(0);

}