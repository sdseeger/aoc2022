#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>

#include "parser.hpp"

int main()
{
    using vi_t = std::vector<int>;
    using vvi_t = std::vector<vi_t>;

    vvi_t vv;

    vv.push_back({});

    aoc::parse(std::cin, [&vv](std::istringstream istr) {
        int val;

        if(istr.peek()!=std::char_traits<char>::eof()) {
            istr >> val;
            vv.back().push_back(val);
        }
        else vv.push_back({});
    });

    uint32_t max=0;

    for(auto &v: vv) {
        uint32_t t=0;

        for(auto &i : v) {
            t += i;
        }

        if(t>max) max=t;
    }

    std::cout << max << std::endl;
    return 0;
}
