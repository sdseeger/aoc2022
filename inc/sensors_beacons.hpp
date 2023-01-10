#ifndef SENSORS_BEACONS__HPP
#define SENSORS_BEACONS__HPP

#include <iostream>
#include <functional>

namespace aoc {
    namespace sensors_beacons {
        using coords_t = std::pair<uint64_t, uint64_t>; /* x, y */

        void parse(std::istream&, const std::function<void(coords_t &&, coords_t &&)>&);

        struct sensor {
            const coords_t pos;
            const coords_t closest_beacon;

            sensor(coords_t &&pos, coords_t &&b):pos(pos), closest_beacon(b) {}

            uint64_t md() const; /* calculate manhattan distance */
            uint64_t md(const coords_t &c) const;
        };
    }
}

#endif
