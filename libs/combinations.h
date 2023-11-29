#ifndef ADVENT_OF_CODE_COMBINATIONS_H
#define ADVENT_OF_CODE_COMBINATIONS_H

#include <bits/stdc++.h>

struct COMBINATIONS
{
    COMBINATIONS(std::vector<int> &arr, int len)
        : elements(arr), current_combination(len), current_indices(len), current_length(len), first(true)
    {
        for (int i = 0; i < current_length; ++i)
        {
            current_indices[i]     = i;
            current_combination[i] = elements[i];
        }
    }

    bool has_next()
    {
        return current_indices[0] < elements.size() - current_length || first;
    }

    std::vector<int> &next()
    {
        if (first)
        { 
        	first =false;
            return current_combination;
        }
        // Find the rightmost index that can be incremented
        int i = current_length - 1;
        while (i >= 0 && current_indices[i] == elements.size() - current_length + i)
            --i;

        if (i >= 0)
        {
            ++current_indices[i];
            current_combination[i] = elements[current_indices[i]];

            // Update subsequent indices and current_combination
            for (int j = i + 1; j < current_length; ++j)
            {
                current_indices[j]     = current_indices[j - 1] + 1;
                current_combination[j] = elements[current_indices[j]];
            }
        }
        return current_combination;
    }

private:
    std::vector<int> &elements;
    std::vector<int> current_combination;
    std::vector<int> current_indices;
    int              current_length;
    bool first;
};

#endif//ADVENT_OF_CODE_COMBINATIONS_H
/*          Uses code 

vector<int> numbers = {1,2,3,4,5};
COMBINATION combinations(numbers, 3);    
while (combinations.has_next())
{
     auto &combination = combinations.next();
		// DO SOMETHING WITH `combination `
}  

*/