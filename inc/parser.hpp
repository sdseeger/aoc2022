#ifndef PARSER__HPP
#define PARSER__HPP

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

namespace aoc {
    using vs_t = std::vector<std::string>;
    using is_t = std::vector<std::istringstream>;

    class break_exception : public std::exception {};

    void parse(std::istream &is, const std::function<void(std::istringstream)>&);
    void parse(std::istream &is, const std::function<void(std::string)>&);
    void parse(std::istream &is, int mod, const std::function<void(vs_t)>&, bool include_incomplete=true);
    void parse(std::istream &is, int mod, const std::function<void(is_t)>&, bool include_incomplete=true);

    void parse_breakable(std::istream &is, const std::function<void(std::istringstream)>&);
    void parse_breakable(std::istream &is, const std::function<void(std::string)>&);
}
#endif
