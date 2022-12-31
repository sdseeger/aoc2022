#include <iostream>
#include <algorithm>

#include "parser.hpp"
#include "distress.hpp"

using namespace aoc;
using namespace aoc::distress;

namespace {
    using vvv_t = std::vector<vv_t>;
}

int main()
{
    vvv_t v;
    const std::string div[2] = {"[[2]]", "[[6]]"};
    vv_t divs[2] = {parse_string(div[0]), parse_string(div[1])};

    aoc::parse(std::cin, 3, [&](vs_t vs) {
        v.emplace_back(parse_string(vs[0]));
        v.emplace_back(parse_string(vs[1]));
    });

    v.emplace_back(divs[0]);
    v.emplace_back(divs[1]);

    std::sort(v.begin(), v.end(), [](const vv_t &l, const vv_t &r) {
        return check_list(std::get<0>(l[0]), std::get<0>(r[0]))==R_DONE_PASS;
    });

    int indexes[2] = {0,0};
    int pos = 0;
    for(const auto &packet : v) {
        ++indexes[pos];
        if(std::get<0>(packet[0])==std::get<0>(divs[pos][0])) {
            indexes[++pos] = indexes[0];
        }
        if(pos==2) break;
    }

    std::cout << indexes[0]*indexes[1] << std::endl;
    return 0;
}
