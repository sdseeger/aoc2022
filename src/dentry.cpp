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

namespace aoc {
    void parse_dentry(dentry_p root)
    {
        dentry *cwd = root;

        aoc::parse_breakable(std::cin, [](std::string) {
            throw aoc::break_exception();
        }); /* ignore first line, the cd / */

        /* build the directory tree */
        aoc::parse(std::cin, [&cwd](std::istringstream istr) {
            /* each line in istr will always have two strings, but cd command has 3 */
            std::string s[2];
            istr >> s[0] >> s[1];

            if(s[0][0]=='$') {
                /* command */
                if(s[1][0] == 'c') {
                    /* change directory */
                    std::string dest;
                    istr >> dest;
                    if(dest=="..") {
                        assert(cwd->parent);
                        cwd->parent->size += cwd->size;
                        cwd = cwd->parent;
                    }
                    else {
                        /* changing to another directory */
                        cwd = std::get<dentry_p>(cwd->map[dest]);
                        assert(cwd);
                    }
                }
                /* NOTE: can ignore ls command, just process as output */
            }
            else {
                /* output of command */
                if(s[0][0]=='d') {
                    /* defining a directory */
                    /* s[0] says "dir", s[1] has dir name */
                    cwd->map.emplace(s[1], new dentry(cwd, s[1]));
                }
                else {
                    /* s[0] has the size, s[1] has the fname */
                    const auto sz = std::stoi(s[0]);
                    cwd->map.emplace(s[1], new file(cwd, sz));
                    cwd->size += sz;
                }
            }
        });
        
        /* move back up to root, filling in sizes along the way */
        while(cwd->parent) {
            cwd->parent->size += cwd->size;
            cwd = cwd->parent;
        }
    }
}
