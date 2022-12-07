#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>

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

    vi_t maxes;
    maxes.reserve(vv.size());

    for(auto &v: vv) {
        uint32_t t=0;

        for(auto &i : v) {
            t += i;
        }

        maxes.push_back(t);
    }

    std::sort(maxes.begin(), maxes.end(), std::greater<vi_t::value_type>());

    assert(maxes.size()>3);
    std::cout << (maxes[0]+maxes[1]+maxes[2]) << std::endl;
    return 0;
}
