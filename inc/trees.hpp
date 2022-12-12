#ifndef TREES__HPP
#define TREES__HPP

#include <vector>
#include <functional>

namespace aoc {
    namespace trees {
        using vi_t = std::vector<uint8_t>;
        /* function should return non-zero to break */
        using fn_t = std::function<int(int /* x */, int /* y */, int /* index */, int /* mindex */)>;

        void parse(vi_t &forest, int &m);

        /* look horizontally along so many rows */
        void look_horiz(int x, int y, int dx, int dy, const vi_t &forest, int m, const fn_t &fn);

        /* look vertically along so many columns */
        void look_vert(int x, int y, int dx, int dy, const vi_t &forest, int m, const fn_t &fn);
    }
}

#endif
