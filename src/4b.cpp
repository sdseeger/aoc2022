#include <iostream>
#include <cstdint>

#include "parser.hpp"

int main()
{
    uint32_t total=0;

    aoc::parse(std::cin, [&total](std::istringstream istr) {
        int32_t vals[4];
        char dummy;
        istr >> vals[0] >> dummy >> vals[1] >> dummy >> vals[2] >> dummy >> vals[3];

        auto f = [](int32_t v, int32_t l, int32_t r) {
            return ((v>=l)&&(v<=r));
        };

        if(f(vals[0], vals[2], vals[3])) ++total;
        else if(f(vals[1], vals[2], vals[3])) ++total;
        else if(f(vals[2], vals[0], vals[1])) ++total;
        else if(f(vals[3], vals[0], vals[1])) ++total;
    });

    std::cout << total << std::endl;
    return 0;
}
