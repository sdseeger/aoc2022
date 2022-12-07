#ifndef PARSER__HPP
#define PARSER__HPP

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {
    using vs_t = std::vector<std::string>;
    void parse(std::istream &is, const std::function<void(std::istringstream)>&);
    void parse(std::istream &is, const std::function<void(std::string)>&);
    void parse(std::istream &is, int mod, const std::function<void(vs_t)>&);
}
#endif
