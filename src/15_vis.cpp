#include <iostream>
#include "sensors_beacons.hpp"

/* this is a simple program to visualize a space. I wanted to make sure I had the right idea
 * on the example input */

using namespace aoc::sensors_beacons;

int main()
{
    std::vector<sensor> vs;

    coords_t mins{100000000,100000000};
    coords_t maxs{-100000000, -100000000};

    parse(std::cin, [&](coords_t &&s, coords_t &&b) {
        vs.emplace_back(std::move(s), std::move(b));
    });

    /* find min/max */
    for(const auto &s : vs) {
        const auto md = s.md();
        if((s.pos.first-md)<mins.first) mins.first = (s.pos.first-md);
        if((s.pos.first+md)>maxs.first) maxs.first = (s.pos.first+md);
        if((s.pos.second-md)<mins.second) mins.second = (s.pos.second-md);
        if((s.pos.second+md)>maxs.second) maxs.second = (s.pos.second+md);
    }

    std::cout << mins.first << ", " << mins.second << " :: " << maxs.first << ", " << maxs.second << std::endl;

    /* fill in the map with pixels */
    const coords_t range{(maxs.first-mins.first+1), (maxs.second-mins.second+1)};
    const int sz = (range.first*range.second);
    std::vector<char> vc;
    vc.reserve(sz);
    for(int i=0; i<sz; ++i) vc.emplace_back('.');

    auto get_index = [&vc, &mins, &range](int x, int y) {
        return ((y+-mins.second)*range.second)+(x+-mins.first);
    };

    for(const auto &s : vs) {
        const auto md = s.md();

        std::cout << s.pos.first << ", " << s.pos.second << ": " << md << std::endl;

        /* fill in pixels */
        for(int y=(s.pos.second-md); y<=(s.pos.second+md); ++y) {
            const int dy = abs(s.pos.second-y);
            if((y>=0)&&(y<=20)) {
                for(int x=(s.pos.first-abs(md-dy)); x<=(s.pos.first+(md-dy)); ++x) {
                    if((x>=0)&&(x<=20)) vc[get_index(x, y)] = '#';
                    //std::cout << x << ", " << y << std::endl;
                }
            }
        }
    }

    /* now go through and mark all the corners */
    for(const auto &s : vs) {
        const auto md = s.md();

        //vc[get_index(s.pos.first, s.pos.second)] = 'S';
        //vc[get_index(s.closest_beacon.first, s.closest_beacon.second)] = 'b';
        vc[get_index(s.pos.first-md, s.pos.second)] = 'L';
        vc[get_index(s.pos.first, s.pos.second-md)] = 'T';
        vc[get_index(s.pos.first+md, s.pos.second)] = 'R';
        vc[get_index(s.pos.first, s.pos.second+md)] = 'B';
    }

    for(int y=0; y<=20; ++y) {
        for(int x=0; x<=20; ++x) {
            std::cout << vc[get_index(x, y)];
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return 0;
}
