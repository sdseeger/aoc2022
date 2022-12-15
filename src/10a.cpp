#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include "parser.hpp"

namespace {
    using opcode_t = std::optional<int>;
    using program_t = std::vector<opcode_t>;

    using add_delay_t = std::pair<int, int>;
    using adder_t = std::vector<add_delay_t>; /* vector of 1 basically */

    void execute(program_t::iterator &iter, int start, int &x, adder_t &adder, int steps)
    {
        for(int i=start; i<steps; ++i) {
            bool fetch=true;
            if(adder.size()) {
                for(auto &a : adder) --a.first;

                if(!adder[0].first) {
                    x += adder[0].second;
                    adder.erase(adder.begin());
                }
                else fetch=false;
            }

            if(fetch) {
                if(iter->has_value()) {
                    adder.emplace_back(2, iter->value());
                }
                ++iter;
            }
        }
    }
}

int main()
{
    program_t program;

    aoc::parse(std::cin, [&program](std::istringstream istr) {
        std::string insn;

        istr >> insn;

        if(insn[0]=='n') {
            program.emplace_back();
        }
        else {
            int val;
            istr >> val;
            program.emplace_back(val);
        }
    });

    /* run through the program */
    uint32_t sum=0;
    static const int steps[7] = { 0, 20, 60, 100, 140, 180, 220 };
    int x=1;
    auto iter = program.begin();
    adder_t adder;

    for(int i=1; i<7; ++i) {
        execute(iter, steps[i-1], x, adder, steps[i]);
        sum += (steps[i]*x);
    }

    std::cout << sum << std::endl;
    return 0;
}
