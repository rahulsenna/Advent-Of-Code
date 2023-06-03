#include <bits/stdc++.h>
using namespace std;


int main()
{
    char input[] = "vzbxkghb";

    while(1)
    {
        input[7]++;

        for (size_t i = 7; i > 0; --i)
        {
        	 if (input[i] <= 'z')             
                break;
             
             input[i] = 'a';
             input[i - 1]++;          
        }
        int three = 0;
        for (size_t i = 0; i <= 5; ++i)
        {
        	 three = 1;
             for (size_t j = 1; j < 3; ++j)
             {
                if (input[i] != input[i+j]-j)
                    break;
                three++;   
             }
             if (three == 3)
                break;
        }


        if (three == 3 && regex_match(input, regex("^.*(\\w)\\1.*(\\w)\\2.*")))
        {
            int debbuger = 3;
        }

    }
    return(0);

}