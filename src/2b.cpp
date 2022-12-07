#include <iostream>
#include <cstdint>

#include "parser.hpp"

int main()
{
    uint32_t score=0;

    aoc::parse(std::cin, [&score](std::istringstream istr) {
        static const uint8_t scores[3][3] = {
            {{3}, // 0 0
            {4},  // 0 1
            {8}}, // 0 2

            {{1}, // 1 0
            {5},  // 1 1
            {9}}, // 1 2

            {{2}, // 2 0
            {6},  // 2 1
            {7}}, // 2 2
        };

        char l, r;
        istr >> l >> r;
        l -= 'A';
        r -= 'X';
        score += scores[l][r];
    });

    std::cout << score << std::endl;
    return 0;
}
