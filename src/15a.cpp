#include <iostream>
#include <set>
#include <vector>
#include "sensors_beacons.hpp"

using namespace aoc::sensors_beacons;

int main(int argc, char **argv)
{
    std::set<coords_t> sc;
    std::vector<sensor> vs;

    if(argc!=2) {
        std::cerr << "usage: ./15a <row>\nwhere row is the one to count open positions" << std::endl;
        return 1;
    }

    const int y = atoi(argv[1]);
    parse(std::cin, [&](coords_t &&s, coords_t &&b) {
        if(b.second==y) {
            sc.emplace(b);
        }
        vs.emplace_back(std::move(s), std::move(b));
    });

    int row_min{100000000};
    int row_max{-100000000};
    for(const auto &s : vs) {
        const auto md = s.md();
        const int dy = abs(s.pos.second-y);
        if(dy<md) {
            const int dx=(md-dy);
            const int rmin = s.pos.first-dx;
            const int rmax = s.pos.first+dx;

            std::cout << ":: " << s.pos.first << ' ' << s.pos.second << ' ' << md << ' ' << dy << ' ' << dx << ' ' << row_min << ' ' << rmin << ' ' << row_max << ' ' << rmin << std::endl;
            if(rmin<row_min) {
                std::cout << "set row_min: " << s.pos.first << ' ' << s.pos.second << ' ' << md << ' ' << dy << ' ' << dx << ' ' << row_min << ' ' << rmin << std::endl;
                row_min = rmin;
            }

            if(rmax>row_max) {
                std::cout << "set row_max: " << s.pos.first << ' ' << s.pos.second << ' ' << md << ' ' << dy << ' ' << dx << ' ' << row_max << ' ' << rmax << std::endl;
                row_max = rmax;
            }
        }
    }

    std::cout << (row_max-row_min+1)-sc.size() << std::endl; /* 7532807 too high */
    return 0;
}
