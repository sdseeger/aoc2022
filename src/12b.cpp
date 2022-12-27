#include <iostream>

#include "elevation.hpp"

using namespace aoc;
using namespace aoc::elevation;

int main()
{
    vs_t vs;

    const auto [start, end] = parse(std::cin, vs);

    /* calculate the max x and y coordinate */
    const coord_t maxs = std::make_pair(vs[0].size(), vs.size());
    //dist_t dist = dijkstra(vs, maxs, start);

    cost_t min = INIT_MIN;

    for(int y=0; y<maxs.second; ++y) {
        for(int x=0; x<maxs.first; ++x) {
            if(vs[y][x]=='a') {
                dist_t dist = dijkstra(vs, maxs, {x, y});
                const int cost = dist[c_to_vi(maxs, end)];
                if(cost<min) min = cost;
            }
        }
    }

    std::cout << min << std::endl;
    return 0;
}
