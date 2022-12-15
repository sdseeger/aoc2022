#include <iostream>
#include <map>

#include "parser.hpp"
#include "monkey.hpp"

using namespace aoc;
using namespace aoc::monkey;

namespace {
    using element_t = uint64_t;
    using item_t = std::vector<element_t>;
    using monkey = aoc::monkey::monkey<item_t>;
    using mv_t = std::vector<monkey>;
}

int main()
{
    mv_t monkeys = aoc::monkey::parse<item_t>([](int val) {
        item_t it;
        it.emplace_back(val);
        return it;
    });
    std::vector<int> num_inspects(monkeys.size());

    /* parse() will only yield items in each monkey having a single item as read from the file */
    for(auto &m : monkeys) {
        std::vector<item_t> its;
        item_t new_it;

        for(auto &it : m.items) {
            for(auto &mm : monkeys) {
                new_it.emplace_back(it[0]%mm.div);
            }
            its.emplace_back(std::move(new_it));
        }

        m.items = its;
    }

    for(int i=0; i<10000; ++i) {
        for(int j=0; j<monkeys.size(); ++j) {
            num_inspects[j] += monkeys[j].items.size();
            for(auto &item : monkeys[j].items) {
                item_t it_new;
                for(int k=0; k<monkeys.size(); ++k) {
                    it_new.emplace_back(monkeys[j].op(item[k])%monkeys[k].div);
                }

                if(!it_new[j]) monkeys[monkeys[j].throw_true].receive_item(it_new);
                else monkeys[monkeys[j].throw_false].receive_item(it_new);
            }
            monkeys[j].items.clear();
        }
    }

    uint64_t max[2]={0,0};
    for(const auto &i : num_inspects) {
        if(i>max[0]) max[0] = i;
    }

    for(const auto &i : num_inspects) {
        std::cout << i << std::endl;
        if((i>max[1])&&(i!=max[0])) max[1] = i;
    }

    std::cout << (uint64_t)(max[0]*max[1]) << std::endl;
    return 0;
}
