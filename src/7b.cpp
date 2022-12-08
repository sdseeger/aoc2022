#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <variant>
#include <utility>
#include <memory>
#include <string>
#include <cassert>

#include "dentry.hpp"
#include "parser.hpp"

using namespace aoc;

int main()
{
    const uint32_t AVAIL = 70000000;
    const uint32_t NEED =  30000000;
    dentry root;
    parse_dentry(&root);

    uint32_t outer=0;
    for(const auto &v : root.map) {
        if(v.second.index()==1) outer += std::get<file_p>(v.second)->size;
        else outer += std::get<dentry_p>(v.second)->size;
    }

    const uint32_t CUR = (AVAIL-outer);

    uint32_t smallest = NEED;
    std::cout << NEED << ' ' << CUR << ' ' << outer << std::endl;
    std::function<void(dentry_p d)> f = [NEED, CUR, &smallest, &f](dentry_p d) {
        for(auto &v: d->map) {
            if(v.second.index()==0) {
                /* only need to look at dir sizes */
                auto d = std::get<dentry_p>(v.second);
                if(((d->size+CUR)>=NEED)&&(d->size<smallest)) smallest = d->size;
                f(d);
            }
        }
    };

    f(&root);
    std::cout << smallest << std::endl;
    return 0;
}
