#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <optional>
#include <algorithm>
#include "parser.hpp"

namespace {
    using opcode_t = std::optional<int>;
    using program_t = std::vector<opcode_t>;

    using add_delay_t = std::pair<int, int>;
    using adder_t = std::vector<add_delay_t>; /* vector of 1 basically */

    using crt_row_t = std::string;
    using crt_t = std::array<crt_row_t, 6>;

    void execute(program_t::iterator &iter, int &x, adder_t &adder, int steps)
    {
        for(int i=0; i<steps; ++i) {
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
    int X=1;
    auto iter = program.begin();
    adder_t adder;
    crt_t crt;

    for(int i=0; i<crt.size(); ++i) crt[i] = "........................................"; /* 40 chars */

    while(iter!=program.end()) {
        for(int y=0; (y<crt.size())&&(iter!=program.end()); ++y) {
            for(int x=0; (x<40)&&(iter!=program.end()); ++x) {
                execute(iter, X, adder, 1);
                /* sprite is 3 pixels, x-1, x, and x+1 */
                if(abs(X-x)<=1) crt[y][x] = '#';
                else crt[y][x] = '.';
            }
        }
    }

    for(const auto &s : crt) std::cout << s << "\n";
    std::cout << std::endl;
    return 0;
}
