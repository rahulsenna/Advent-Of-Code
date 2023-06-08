#include <bits/stdc++.h>
using namespace std;

struct COMBINATION
{
    COMBINATION(std::vector<int> &arr)
    {
        elements            = arr;
        current_combination = std::vector<int>(elements.size());
        current_indices     = std::vector<int>(elements.size());
    }

    void of_length(int len)
    {
        current_length = len;
        for (int i = 0; i < current_length; ++i)
        {
            current_indices[i]     = i;
            current_combination[i] = elements[i];
        }
    }

    bool has_next()
    {
        return current_indices[0] < elements.size() - current_length;
    }

    std::vector<int> &next()
    {
        // Find the rightmost index that can be incremented
        int i = current_length - 1;
        while (i >= 0 && current_indices[i] == elements.size() - current_length + i)
            --i;

        if (i >= 0)
        {
            ++current_indices[i];
            current_combination[i] = elements[current_indices[i]];

            // Update subsequent indices and currentCombination
            for (int j = i + 1; j < current_length; ++j)
            {
                current_indices[j]     = current_indices[j - 1] + 1;
                current_combination[j] = elements[current_indices[j]];
            }
        }
        return current_combination;
    }

private:
    std::vector<int> elements;
    std::vector<int> current_combination;
    std::vector<int> current_indices;
    int              current_length;
};

int main() {
    ifstream inputFile("input.txt");

    int containers = 0, min_containers = 0;

    vector<int> numbers(istream_iterator<int>(inputFile), {});
    COMBINATION combinations(numbers);    
    for (int i = 1; i <= numbers.size(); ++i)
    {
        combinations.of_length(i);
        while (combinations.has_next())
        {
             auto &combination = combinations.next();
             auto sum = accumulate(combination.begin(), combination.end(), 0);
             if (sum == 150)
                 containers++;
        }
        if (!min_containers && containers)
            min_containers = containers;
    }

    std::cout << "containers: " << containers << '\n';
    std::cout << "min_containers: " << min_containers << '\n';

    // Speed Intel i5 7400
    // Debug  :  0.152406 seconds
    // Release:  5.4e-05 seconds  (0.000054)
    return 0;
}
