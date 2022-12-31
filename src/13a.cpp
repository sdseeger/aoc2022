#include <iostream>
#include <cassert>

#include "parser.hpp"
#include "distress.hpp"

using namespace aoc;
using namespace aoc::distress;

namespace {
    using a_t = std::array<vv_t, 2>;
    using va_t = std::vector<a_t>;
    res_t check_lists(const vv_t &l, const vv_t &r)
    {
        /* first item in l and r are a list */
        return check_list(std::get<0>(l[0]), std::get<0>(r[0]));
    }
}

int main()
{
    va_t va;

    va.reserve(128);

    parse(std::cin, 3, [&](vs_t vs) {
        va.emplace_back(a_t{parse_string(vs[0]), parse_string(vs[1])});
    });

    int total=0;
    int i=1;
    for(const auto &a : va) {
        if(check_lists(a[0], a[1])==R_DONE_PASS) {
            total += i;
        }
        ++i;
    }

    std::cout << total << std::endl;
    return 0;
}
