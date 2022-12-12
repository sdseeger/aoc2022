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

    uint32_t max_score=0;
    for(int y=0; y<m; ++y) {
        for(int x=0; x<m; ++x) {
            /* look in all directions from here */
            uint32_t lmax=1;
            int nx, ny;
            int min=0;
            int old=-1;
            auto f = [&forest, &min, &old, &nx, &ny](int x, int y, int index, int mindex) -> int {
                if(mindex!=old) {
                    min = forest[mindex];
                    old = mindex;
                }
                else {
                    const auto v = forest[index];
                    if(v>=min) {
                        nx=x;
                        ny=y;
                        return 1;
                    }
                }

                return 0;
            };

            nx=m-1;
            ny=y;
            look_horiz(x, y, m, y, forest, m, f);
            lmax = (nx-x);

            min=0;
            old=-1;
            nx=0;
            ny=y;
            look_horiz(x, y, 0, y, forest, m, f);
            lmax *= (x-nx);

            min=0;
            old=-1;
            ny=m-1;
            nx=x;
            look_vert(x, y, x, m, forest, m, f);
            lmax *= (ny-y);

            min=-1;
            old=-1;
            ny=0;
            nx=x;
            look_vert(x, y, x, 0, forest, m, f);
            lmax *= (y-ny);

            if(lmax>max_score) max_score = lmax;
        }
    }

    std::cout << max_score << std::endl;
    return 0;
}
