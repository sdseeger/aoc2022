#ifndef SAND__HPP
#define SAND__HPP

#include <map>
#include "parser.hpp"

namespace aoc {
    namespace sand {
        using coord_t = std::pair<int, int>; /* x, y */
        using grid_t = std::map<coord_t, char>;

        const coord_t sand{500, 0};

        coord_t extract(std::istringstream &istr, coord_t &mins, coord_t &maxs);
        void draw(const grid_t &grid, const coord_t &mins, const coord_t &maxs);
        void parse(grid_t &grid, coord_t &mins, coord_t &maxs);
    }
}

#endif
