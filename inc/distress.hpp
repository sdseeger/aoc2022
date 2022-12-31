#ifndef DISTRESS__HPP
#define DISTRESS__HPP

#include <variant>
#include <vector>
#include <stack>
#include <string>

namespace aoc {
    namespace distress {
        using element_t = int;
        struct vi_t;
        using v_t = std::variant<std::vector<vi_t>, element_t>;
        struct vi_t {
            v_t v;
        };

        bool operator==(const vi_t &l, const vi_t &r);

        using vv_t = std::vector<v_t>;
        using vvi_t = std::vector<vi_t>;
        using s_t = std::stack<v_t*>;

        typedef enum res {
            R_CONTINUE,
            R_DONE_FAIL,
            R_DONE_PASS
        } res_t;

        vv_t parse_string(const std::string &str);
        res_t check_list(const vvi_t&, const vvi_t&);
    }
}

#endif
