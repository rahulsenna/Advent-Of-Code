#include <bits/stdc++.h>
using namespace std;


int main() {
    ifstream file("input.txt");

    string label, line;
    vector<uint64_t> seeds;

    getline(file, line);
    stringstream ss(line);
    ss >> label;
    seeds = {istream_iterator<uint64_t>(ss), {}};

    vector<pair<uint64_t, uint64_t>> seed_ranges;
    for (size_t i = 0; i < seeds.size(); i += 2)
        seed_ranges.emplace_back(seeds[i], seeds[i] + seeds[i + 1]);

    vector<vector<vector<uint64_t>>> maps(7);
    int idx = -1;
    
    while (getline(file, line)) {
        if (line.empty()) {
            getline(file, line);
            ++idx;
            continue;
        }
        stringstream ss(line);
        maps[idx].emplace_back(istream_iterator<uint64_t>(ss), istream_iterator<uint64_t>());
    }

    for (auto &map : maps)
    {
        for (auto &seed : seeds)
        {
            for (auto &m : map)
            {
                auto [dest, src, range] = tuple(m[0], m[1], m[2]);
                if (seed > src && seed < src + range)
                {
                    seed -= (src - dest);
                    break;
                }
            }
        }
    }

    for (auto &map : maps) {
        vector<pair<uint64_t, uint64_t>> new_seeds;
        
        while (!seed_ranges.empty()) {
            auto [beg, end] = seed_ranges.back();
            seed_ranges.pop_back();
            bool found = false;

            for (auto &m : map) {
                auto [dest, src, range] = tuple(m[0], m[1], m[2]);
                auto i_sec_beg = max(beg, src);
                auto i_sec_end = min(end, src + range);

                if (i_sec_beg < i_sec_end) {
                    found = true;
                    new_seeds.emplace_back(i_sec_beg - (src - dest), i_sec_end - (src - dest));

                    if (beg < i_sec_beg)
                        seed_ranges.emplace_back(beg, i_sec_beg);

                    if (end > i_sec_end)
                        seed_ranges.emplace_back(i_sec_end, end);
                    break;
                }
            }
            if (!found)
                new_seeds.emplace_back(beg, end);
        }

        seed_ranges = new_seeds;
    }

    auto res1 = *min_element(seeds.begin(), seeds.end());
    printf("part1: %llu\n", res1);

    auto res2 = *min_element(seed_ranges.begin(), seed_ranges.end(), [](auto &a, auto &b) {return a.first < b.first;});
    printf("part2: %llu\n", res2.first);

    

    return 0;
}
