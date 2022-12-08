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
    dentry root;
    parse_dentry(&root);

    uint32_t sum=0;
    /* walk through the root and look for directories under 100000 bytes and add them up */
    std::function<void(dentry_p d)> f = [&f, &sum](dentry_p d) {
        uint32_t lsum=d->size;
        for(auto &v : d->map) {
            if(v.second.index()==0) {
                dentry_p d = std::get<dentry_p>(v.second);
                f(d);
            }
            else {
                //file_p 
            }
        }

        if(lsum<=100000) {
            sum += lsum;
        }
    };

    f(&root);
    std::cout << sum << std::endl;
    return 0;
}
