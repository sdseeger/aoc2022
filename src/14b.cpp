#include <iostream>

#include "sand.hpp"

using namespace aoc::sand;

int main()
{
    grid_t grid;
    coord_t maxs{0,0};
    coord_t mins{1000000,1000000};

    parse(grid, mins, maxs);
    std::cout << mins.first << ", " << mins.second << " :: " << maxs.first << ", " << maxs.second << std::endl;
    
    maxs.second += 2;

    /* now drop the sand */
    int total=0;
    for(;;) {
        static const coord_t deltas[3] = { {0, 1}, {-1, 1}, {1, 1} };
        coord_t s = sand;

        for(int i=0; i<3; ++i) {
            for(;;) {
                coord_t sn{s};

                sn.first += deltas[i].first;
                sn.second += deltas[i].second;

                if(sn.second==maxs.second) break; /* going to fall past new floor */

                auto it = grid.find(sn);
                if(it!=grid.end()) break; /* we can't move here */
                s = sn;
                i = 0; /* restart the step attempts */
            }
        }

        ++total;
        grid[s] = 'o';
        if(s==sand) break;
    }

    std::cout << total << std::endl;
    return 0;
}
