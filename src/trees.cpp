#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <variant>
#include <utility>
#include <memory>
#include <cstring>
#include <cassert>

#include "trees.hpp"
#include "parser.hpp"

namespace aoc {
    namespace trees {
        using vi_t = std::vector<uint8_t>;
        
        void parse(vi_t &forest, int &m)
        {
            aoc::parse_breakable(std::cin, [&forest](std::string s) {
                for(const auto &c : s) {
                    forest.emplace_back(c);
                }
                throw aoc::break_exception();
            });

            m = forest.size(); //now the M is known

            aoc::parse(std::cin, [&forest](std::string s) {
                for(const auto &c : s) {
                    forest.emplace_back(c);
                }
            });
        }

        void look_horiz(int x_, int y_, int dx, int dy, const vi_t &forest, int m, const fn_t &fn)
        {
            const int dxp = (dx>=x_)?1:-1;
            const int dyp = (dy>=y_)?1:-1;
            for(int y=y_; (dyp>0)?((y<=dy)&&(y<m)):((y>=dy)&&(y>=0)); y+=dyp) {
                const int mindex = (y*m)+x_;
                for(int x=x_; (dxp>0)?((x<=dx)&&(x<m)):((x>=dx)&&(x>=0)); x+=dxp) {
                    const int index = (y*m)+x;
                    if(fn(x, y, index, mindex)) return;
                }
            }
        }

        void look_vert(int x_, int y_, int dx, int dy, const vi_t &forest, int m, const fn_t &fn)
        {
            const int dxp = (dx>=x_)?1:-1;
            const int dyp = (dy>=y_)?1:-1;
            for(int x=x_; (dxp>0)?((x<=dx)&&(x<m)):((x>=dx)&&(x>=0)); x+=dxp) {
                const int mindex = (y_*m)+x;
                for(int y=y_; (dyp>0)?((y<=dy)&&(y<m)):((y>=dy)&&(y>=0)); y+=dyp) {
                    const int index = (y*m)+x;
                    if(fn(x, y, index, mindex)) return;
                }
            }
        }
    }
}
