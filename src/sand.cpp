#include <iostream>
#include "sand.hpp"
#include "parser.hpp"

namespace aoc {
    namespace sand {
        coord_t extract(std::istringstream &istr, coord_t &mins, coord_t &maxs)
        {
            int a, b;

            istr >> a;
            istr.ignore();
            istr >> b;

            /* update mins and maxs */
            if(a<mins.first) mins.first = a;
            if(a>maxs.first) maxs.first = a;
            if(b<mins.second) mins.second = b;
            if(b>maxs.second) maxs.second = b;

            return std::make_pair(a, b);
        }

        void draw(const grid_t &grid, const coord_t &mins, const coord_t &maxs)
        {
            for(int y=mins.second; y<=maxs.second; ++y) {
                for(int x=mins.first; x<= maxs.first; ++x) {
                    coord_t c{x, y};
                    auto it = grid.find(c);
                    if(it==grid.end()) std::cout << '.';
                    else std::cout << it->second;
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }

        void parse(grid_t &grid, coord_t &mins, coord_t &maxs)
        {
            aoc::parse(std::cin, [&](std::istringstream istr) {
                coord_t cs[2]; /* need two points to do anything */
                coord_t cur;
                istr.exceptions(std::ios::failbit);
                try {
                    /* there should always be at least two points */
                    cs[0] = extract(istr, mins, maxs);
                    istr.ignore(3);
                    cs[1] = extract(istr, mins, maxs);
                    for(;;) {
                        /* draw a line in the grid */
                        int dx, dy;

                        if(cs[0].first==cs[1].first) {
                            /* vert */
                            dx = 0;
                            dy = (cs[0].second<cs[1].second)?1:-1;
                        }
                        else {
                            /* vertical */
                            dy = 0;
                            dx = (cs[0].first<cs[1].first)?1:-1;
                        }

                        cur = cs[0];
                        grid[cur] = '#';
                        do {
                            cur.first += dx;
                            cur.second += dy;
                            grid[cur] = '#';
                        }
                        while(cur!=cs[1]);

                        cs[0] = cs[1];
                        istr.ignore(3);
                        cs[1] = extract(istr, mins, maxs);
                    }
                }
                catch(...) {
                    /* discard exception, used as loop terminator */
                }
            });
        }
    }
}
