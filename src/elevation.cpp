#include <cstring>
#include <climits>
#include <queue>
#include <set>

#include "elevation.hpp"

using namespace aoc::elevation;

namespace {
    cv_t neighbors(const coord_t &m, const coord_t &c)
    {
        cv_t ret(4); /* max is 4 neighbors */

        /* left, only if x is > 0 */
        if(c.first>0) ret.emplace_back(std::make_pair(c.first-1, c.second));

        /* right */
        if(c.first<(m.first-1)) ret.emplace_back(std::make_pair(c.first+1, c.second));

        /* top */
        if(c.second>0) ret.emplace_back(std::make_pair(c.first, c.second-1));

        /* bottom */
        if(c.second<(m.second-1)) ret.emplace_back(std::make_pair(c.first, c.second+1));

        return ret;
    }
}

namespace aoc {
    namespace elevation {
        std::pair<coord_t, coord_t> parse(std::istream &ifs, vs_t &vs)
        {
            const auto [start, end] = [&]() -> std::pair<coord_t, coord_t> {
                oc_t start, end;
                aoc::parse(ifs, [&](std::string str) {
                    if(!start) {
                        auto x = str.find('S');
                        if(x!=std::string::npos) {
                            start = std::make_pair(x, vs.size());
                            str[x] = 'a'; /* don't include 'S' */
                        }
                    }

                    if(!end) {
                        auto x = str.find('E');
                        if(x!=std::string::npos) {
                            end = std::make_pair(x, vs.size());
                            str[x] = 'z'; /* don't include 'E' */
                        }
                    }
                    vs.emplace_back(std::move(str));
                });

                return {*start, *end};
            }();

            return {start, end};
        }

        int c_to_vi(const coord_t &m, const coord_t &c)
        {
            return (m.first*c.second)+c.first;
        }

        dist_t dijkstra(vs_t &vs, const coord_t &maxs, const coord_t &start)
        {
            const size_t sz = maxs.first*maxs.second;
            std::set<coord_t> cs;
            using qv_t = std::pair<cost_t, coord_t>;
            auto cmp = [](const qv_t &left, const qv_t &right) { return left.first > right.first; };
            std::priority_queue<qv_t, std::vector<qv_t>, decltype(cmp)> q(cmp);
            dist_t dist(sz);

            for(int x=0; x<sz; ++x) dist[x] = INIT_MIN;
            dist[c_to_vi(maxs, start)] = 0;

            for(int y=0; y<maxs.second; ++y) {
                for(int x=0; x<maxs.first; ++x) {
                    cs.insert(std::make_pair(x, y));
                }
            }

            while(cs.size()) {
                /* find vertex with lowest dist */
                cost_t min = INIT_MIN;
                oc_t min_coords;
                while(q.size()) {
                    auto v = q.top();
                    q.pop();
                    if(!cs.contains(v.second)) continue;
                    min_coords = v.second;
                    break;
                }
                if(!min_coords) {
                    for(auto &c : cs) {
                        const int ci = c_to_vi(maxs, c);
                        if(dist[ci]<min) {
                            min = dist[ci];
                            min_coords = c;
                        }
                    }
                }
                if(!min_coords) return dist; /* can't reach anymore */
                cs.erase(*min_coords);

                /* check distance to neighbors */
                auto ns = neighbors(maxs, *min_coords);
                const int ni = c_to_vi(maxs, *min_coords);
                const char ch = vs[min_coords->second][min_coords->first];
                for(const auto &n : ns) {
                    if(cs.contains(n)) {
                        const char nch = vs[n.second][n.first];

                        if((nch<=(ch+1))) {
                            const int ci = c_to_vi(maxs, n);
                            cost_t tot = dist[ni]+1;
                            if(tot<dist[ci]) {
                                dist[ci] = tot;
                                q.push(std::make_pair(tot, n));
                            }
                        }
                    }
                }
            }

            return dist;
        }
    }
}
