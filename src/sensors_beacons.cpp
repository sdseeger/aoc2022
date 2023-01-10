#include <iostream>
#include <map>

#include "parser.hpp"
#include "sensors_beacons.hpp"

namespace aoc {
    namespace sensors_beacons {
        void parse(std::istream &is, const std::function<void(coords_t &&, coords_t &&)> &fn) {
            aoc::parse(std::cin, [&](std::istringstream istr) {
                coords_t s, b;

                istr.ignore(12); /* ignore 'Sensor at x=' */
                istr >> s.first;
                istr.ignore(4); /* ignore ', y=' */
                istr >> s.second;
                istr.ignore(25); /* ignore ': closest beacon is at x=' */
                istr >> b.first;
                istr.ignore(4); /* ignore ', y=' */
                istr >> b.second;

                std::cout << s.first << ' ' << s.second << ' ' << b.first << ' ' << b.second << std::endl;
                fn(std::move(s), std::move(b));
            });
        }

        uint64_t sensor::md() const
        {
            return abs(pos.first-closest_beacon.first) + abs(pos.second-closest_beacon.second);
        }

        uint64_t sensor::md(const coords_t &c) const
        {
            return abs(pos.first-c.first) + abs(pos.second-c.second);
        }
    }
}
