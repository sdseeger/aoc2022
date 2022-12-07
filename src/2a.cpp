#include <iostream>
#include <cstdint>

#include "parser.hpp"

int main()
{
    uint32_t score=0;

    aoc::parse(std::cin, [&score](std::istringstream istr) {
        static const uint8_t scores[3][3] = {
            {{3}, // 0 0
            {0},  // 0 1
            {6}}, // 0 2

            {{6}, // 1 0
            {3},  // 1 1
            {0}}, // 1 2

            {{0}, // 2 0
            {6},  // 2 1
            {3 }}, // 2 2
        };

        char l, r;
        istr >> l >> r;
        l -= 'A';
        r -= 'X';
        score += r+1;
        score += scores[r][l];
    });

    std::cout << score << std::endl;
    return 0;
}
