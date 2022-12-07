#include <iostream>
#include <cstdint>
#include <set>
#include <ctype.h>
#include "parser.hpp"

int main()
{
    uint32_t sum=0;
    aoc::parse(std::cin, 3, [&sum](aoc::vs_t v) {
        using sc_t = std::set<char>;
        sc_t sets[3];
        int i=0;

        for(auto &s: v) {
            for(auto &c: s) {
                sets[i].insert(c);
            }

            ++i;
        }

        for(auto &c: sets[0]) {
            if(sets[1].contains(c)&&sets[2].contains(c)) {
                if(islower(c)) sum += c-'a'+1;
                else sum += c-'A'+27;
            }
        }
    });

    std::cout << sum << std::endl;
    return 0;
}
