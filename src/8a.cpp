#include <iostream>
#include <vector>
#include <cstring>

#include "trees.hpp"

using namespace aoc::trees;

int main()
{
    vi_t forest; /* the vector of integers */
    int m; /* the M, in MxM matrix */

    parse(forest, m);

    vi_t view(forest);
    memset(view.data(), 0, view.size());

    int old=-1;
    uint8_t min=0;
    auto f = [&forest, &view, &min, &old](int x, int y, int index, int mindex) -> int {
        if(mindex!=old) {
            min = forest[mindex];
            view[index] = 1;
            old = mindex;
        }

        const auto v = forest[index];
        if(v>min) {
            view[index] = 1;
            min = v;
        }

        return 0;
    };

    look_horiz(0, 0, m-1, m-1, forest, m, f);

    min=0;
    old=-1;
    look_horiz(m-1, m-1, 0, 0, forest, m, f);

    min=0;
    old=-1;
    look_vert(0, 0, m-1, m-1, forest, m, f);

    min=0;
    old=-1;
    look_vert(m-1, m-1, 0, 0, forest, m, f);

    int x=0;
    for(const auto &v : view) {
        std::cout << !!v;
        if(++x==m) {
            x=0;
            std::cout << "\n";
        }
    }

    uint32_t sum=0;
    for(const auto &v: view) sum += v;
    std::cout << sum << std::endl;
    return 0;
}
