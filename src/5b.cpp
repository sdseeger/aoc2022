#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <span>

#include "parser.hpp"

int main()
{
    using vv_t = std::vector<char>;
    using vs_t = std::vector<vv_t>;
    vs_t vs;

    auto build_stack = [&vs](std::string s) {
        int i, j;
        const std::span sp{s};

        for(i=0, j=0; i<s.size(); i+=4, ++j) {
            auto sp_ = sp.subspan(i, 3);
            if(sp_[1]!=' ') {
                vs[j].emplace_back(sp_[1]);
            }
        }
    };

    /* the first line contains what we need to build the stacks vector */
    aoc::parse_breakable(std::cin, [&vs, &build_stack](std::string s) {
        const uint32_t num_stacks = ((s.size()+1)/4); /* 4 chars per stack */
        for(int i=0; i<num_stacks; ++i) vs.emplace_back();
        build_stack(s);
        throw aoc::break_exception();
    });

    aoc::parse_breakable(std::cin, [&vs, &build_stack](std::string s) {
        if(s.empty()) throw aoc::break_exception();
        if(s.at(1)!='1') build_stack(s);
    });

    /* at this point, the stacks are built */
    /* print top of stacks for debug */
    for(auto &sc : vs) {
        std::cout << sc.front() << ' ';
    }
    std::cout << "\n";

    /* the rest of the parsing are the move instructions */
    aoc::parse(std::cin, [&vs](std::istringstream istr) {
        uint32_t quantity, from, to;
        istr.seekg(5, std::ios_base::cur);
        istr >> quantity;
        istr.seekg(6, std::ios_base::cur);
        istr >> from;
        istr.seekg(4, std::ios_base::cur);
        istr >> to;

        --from;
        --to;
        for(int i=(quantity-1); i>=0; --i) {
            vs[to].emplace(vs[to].begin(), vs[from][i]);
        }
        vs[from].erase(vs[from].begin(), vs[from].begin()+quantity);
    });

    for(auto &sc : vs) {
        std::cout << sc.front() << ' ';
    }
    std::cout << std::endl;

    return 0;
}
