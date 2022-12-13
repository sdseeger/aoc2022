#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "parser.hpp"

namespace {
    enum {
        X,
        Y
    };

    struct coords_t {
        int c[2];
        coords_t():c{0, 0} {}
        coords_t(int x, int y):c{x, y} {}
    };

    bool operator<(const coords_t &l, const coords_t &r) {
        return std::tie(l.c[X], l.c[Y]) < std::tie(r.c[X], r.c[Y]);
    }

    using sc_t = std::set<coords_t>;
    using cv_t = std::vector<coords_t>;
    const int NUM_KNOTS = 10;
}

int main()
{
    cv_t cs(10);

    sc_t visited;
    visited.insert({0, 0}); /* make sure starting point is included */

    aoc::parse(std::cin, [&](std::istringstream istr) {
        char dir;
        int steps;
        istr >> dir >> steps;

        std::cout << dir << ' ' << steps << std::endl;

        const int delta = ((dir=='D')||(dir=='R'))?1:-1;
        const int index = ((dir=='L')||(dir=='R'))?X:Y;

        for(int i=0; i<steps; ++i) {
            cs[0].c[index] += delta;
            for(int j=1; j<NUM_KNOTS; ++j) {
                int dx = abs(cs[j-1].c[X]-cs[j].c[X]);
                int dy = abs(cs[j-1].c[Y]-cs[j].c[Y]);

                /* TODO: clean this up some day */
                /* TODO: forget to clean this up some day */
                if(dx==2) {
                    if(dy) {
                        cs[j].c[X] += (cs[j-1].c[X]>cs[j].c[X])?1:-1;
                        cs[j].c[Y] += (cs[j-1].c[Y]>cs[j].c[Y])?1:-1;
                    }
                    else cs[j].c[X] += (cs[j-1].c[X]>cs[j].c[X])?1:-1;
                }
                else if(dy==2) {
                    if(dx) {
                        cs[j].c[X] += (cs[j-1].c[X]>cs[j].c[X])?1:-1;
                        cs[j].c[Y] += (cs[j-1].c[Y]>cs[j].c[Y])?1:-1;
                    }
                    else cs[j].c[Y] += (cs[j-1].c[Y]>cs[j].c[Y])?1:-1;
                }
            }

            visited.insert({cs[NUM_KNOTS-1].c[X], cs[NUM_KNOTS-1].c[Y]});
        }
    });

    std::cout << visited.size() << std::endl;
    return 0;
}

