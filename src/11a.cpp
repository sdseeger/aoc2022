#include <iostream>

#include "parser.hpp"
#include "monkey.hpp"

using namespace aoc;
using namespace aoc::monkey;

namespace {
    using item_t = uint64_t;
    using monkey = aoc::monkey::monkey<item_t>;
    using mv_t = std::vector<monkey>;
}

namespace {
    void process_items(monkey &m, mv_t &monkeys)
    {
        /* each item gets processed and thrown */
        /* to make it easy, iterate over all items, process and throw them
         * (technically this makes a duplicate for a short time)
         * Then, clear the items vector */
        for(auto &i : m.items) {
            item_t ni = m.op(i);
            ni /= 3;
            if(!(ni%m.div)) monkeys[m.throw_true].receive_item(ni);
            else monkeys[m.throw_false].receive_item(ni);
        }

        m.items.clear();
    }
}

int main()
{
    mv_t monkeys = aoc::monkey::parse<item_t>([](int val) { return val; });
    std::vector<int> num_inspects(monkeys.size());

    for(int i=0; i<20; ++i) {
        for(int j=0; j<monkeys.size(); ++j) {
            num_inspects[j] += monkeys[j].items.size();
            process_items(monkeys[j], monkeys);
        }
    }

    int max[2]={0,0};
    for(const auto &i : num_inspects) {
        if(i>max[0]) max[0] = i;
    }

    for(const auto &i : num_inspects) {
        if((i>max[1])&&(i!=max[0])) max[1] = i;
    }

    std::cout << (max[0]*max[1]) << std::endl;
    return 0;
}
