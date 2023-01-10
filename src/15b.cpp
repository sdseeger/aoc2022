#include <iostream>
#include <set>
#include <cstdint>

#include "sensors_beacons.hpp"

using namespace aoc::sensors_beacons;

int main(int argc, char **argv)
{
    using coeffs = std::set<uint64_t>;
    std::vector<sensor> vs;
    coeffs sa, sb;

    if(argc!=2) {
        std::cerr << "usage: ./15b <max_coord>\nwhere max_coord is the max coord in either x or y (0 lowest)" << std::endl;
        return 1;
    }

    const int max_coord = atoi(argv[1]);

    parse(std::cin, [&](coords_t &&sc, coords_t &&bc) {
        vs.emplace_back(std::move(sc), std::move(bc));
    });

    /* i wasn't able to figure out this one, so i took some inspiration from i_have_no_biscuits on reddit */
    for(const auto &s : vs) {
        const auto md = s.md();
        sa.insert(s.pos.second-s.pos.first+md+1);
        sa.insert(s.pos.second-s.pos.first+md-1);
        sb.insert(s.pos.first+s.pos.second+md+1);
        sb.insert(s.pos.first+s.pos.second+md-1);
    }

    for(const auto &a : sa) {
        for(const auto &b : sb) {
            if(((b-a)&1)) continue;
            const coords_t p{(b-a)/2, (a+b)/2};
            if((0<=p.first)&&(p.first<=max_coord)&&(0<=p.second)&&(p.second<=max_coord)) {
                bool pass=true;
                for(const auto &s : vs) {
                    if(s.md(p)<=s.md()) {
                        pass=false;
                        break;
                    }
                }
                if(pass) std::cout << ((4000000*p.first)+p.second) << std::endl;
            }
        }
    }
    return 0;
}
