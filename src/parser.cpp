#include "parser.hpp"

#include <string>

namespace aoc {
/* TODO: could inline parse() in the header file if it remains this simple */
void parse(std::istream &is, const std::function<void(std::istringstream)> &f)
{
    std::string line;

    while(std::getline(is, line)) {
        std::istringstream istr(line);

        if(istr.good()) f(std::move(istr));
    }
}

void parse(std::istream &is, const std::function<void(std::string)> &f)
{
    std::string line;

    while(std::getline(is, line)) {
        f(std::move(line));
    }
}

void parse(std::istream &is, int mod, const std::function<void(vs_t)> &f)
{
    std::string line;
    int i=0;
    vs_t v;

    while(std::getline(is, line)) {
        v.emplace_back(line);
        if(++i==mod) {
            f(std::move(v));
            v.clear();
            i=0;
        }
    }
}

}
