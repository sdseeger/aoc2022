#include <iostream>
#include <set>
#include <cstdlib>

#include "parser.hpp"

namespace {
                          /*    x    y  */
    using coords_t = std::pair<int, int>;
    using sc_t = std::set<coords_t>;

    /* these really should be locally scoped, but whatever */
    /* makes it easier to set up the structure below without taking up room in main() */
    int hx, hy, tx, ty;

    struct dirs_t {
        int *v;
        int delta;
    };

    dirs_t dirs[26];

    __attribute__((constructor)) void sorry_unimplemented_non_trivial_designated_initializers_not_supported(void)
    {
        dirs['R'] = { &hx, 1 };
        dirs['L'] = { &hx, -1 };
        dirs['D'] = { &hy, 1 };
        dirs['U'] = { &hy, -1 };
    }
}

int main()
{
    sc_t visited;

    visited.insert(std::make_pair(0, 0)); /* make sure starting point is included */

    aoc::parse(std::cin, [&visited](std::istringstream istr) {
        char dir;
        int steps;
        istr >> dir >> steps;

        for(int i=0; i<steps; ++i) {
            /* step the head, then step the tail */
            int ox = hx;
            int oy = hy;

            *dirs[dir].v += dirs[dir].delta;

            if((abs(hx-tx)>1)||(abs(hy-ty)>1)) {
                tx = ox;
                ty = oy;
                visited.insert(std::make_pair(tx, ty));
            }
        }
    });

    std::cout << visited.size() << std::endl;
    return 0;
}

