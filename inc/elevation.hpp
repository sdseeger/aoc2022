#ifndef ELEVATION__HPP
#define ELEVATION__HPP

#include <vector>
#include <optional>
#include "parser.hpp"

namespace aoc {
    namespace elevation {
        using coord_t = std::pair<int, int>; /* x, y */
        using oc_t = std::optional<coord_t>;
        using cost_t = int;
        using dist_t = std::vector<cost_t>;
        using cv_t = std::vector<coord_t>;

        const cost_t INIT_MIN=100000000;

        int c_to_vi(const coord_t &m, const coord_t &c);
        dist_t dijkstra(aoc::vs_t &vs, const coord_t &maxs, const coord_t &start);
        std::pair<coord_t, coord_t> parse(std::istream&, vs_t &vs);
    }
}

#endif
