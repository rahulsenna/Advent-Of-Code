#include <bits/stdc++.h>
using namespace std;


int main()
{
    ifstream file("input.txt");

    int f_p_1,f_p_2;
    int s_p_1,s_p_2;
    char _;

    int sum = 0;
    int sum2 = 0;

    for(string line; file >> f_p_1 >> _ >> f_p_2 >> _  >> s_p_1 >> _ >> s_p_2;)
    {
        if ((f_p_1 <= s_p_1 && f_p_2 >= s_p_2) || (f_p_1 >= s_p_1 && f_p_2 <= s_p_2))
            sum++;
        if ((f_p_1 <= s_p_1 && f_p_2 >= s_p_1) || (s_p_1 <= f_p_1 && s_p_2 >= f_p_1))
            sum2++;
    }
    printf("part1: %d\n", sum);
    printf("part2: %d\n", sum2);
	return(0);
}