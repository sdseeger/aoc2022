#include <algorithm>
#include <iostream>
#include <cstdint>
#include <set>
#include <ctype.h>
#include "parser.hpp"

int main()
{
    uint32_t sum=0;
    aoc::parse(std::cin, [&sum](std::string s) {
        const uint32_t len = s.size();
        const uint32_t each = len/2;

        /* since aoc input is always correct, assume length is divisible by 2 */
        using sc_t = std::set<char>;
        sc_t sets[2];
        int i;

        auto f = [](char c) {
            if(islower(c)) return c-'a'+1;
            else return c-'A'+27;
        };

        for(i=0; i<each; ++i) sets[0].emplace(s.at(i));
        for(i=each; i<len; ++i) sets[1].emplace(s.at(i));

        sc_t set_intersection;
        std::set_intersection(sets[0].begin(), sets[0].end(), sets[1].begin(), sets[1].end(), std::inserter(set_intersection, set_intersection.begin()));

        for(auto &k: set_intersection) {
            sum += f(k);
        }
    });

    std::cout << sum << std::endl;
    return 0;
}
