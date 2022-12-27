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
    dist_t dist = dijkstra(vs, maxs, start);

    std::cout << dist[c_to_vi(maxs, end)] << std::endl;
    return 0;
}
