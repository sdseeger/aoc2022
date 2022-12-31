#include "distress.hpp"

namespace aoc {
    namespace distress {
        vv_t parse_string(const std::string &str)
        {
            vv_t ret;
            v_t *cur;
            s_t s;

            ret.reserve(128);
            ret.emplace_back(std::vector<vi_t>());
            cur = &ret[0];

            s.push(nullptr); /* something for last ], which won't be used */

            /* skip first [ */
            for(int i=1; i<str.size(); ++i) {
                const char ch = str[i];
                if(ch=='[') {
                    std::get<0>(*cur).emplace_back(std::vector<vi_t>());
                    s.push(cur);
                    cur = &std::get<0>(*cur).back().v;
                }
                else if(ch==']') {
                    cur = s.top();
                    s.pop();
                }
                else if((ch>='0')&&(ch<='9')) {
                    const char nch = str[i+1];
                    element_t val = ch-'0';
                    if((nch!=',')&&(nch!='[')&&(nch!=']')) {
                        val *= 10;
                        val += (str[i+1]-'0');
                        ++i;
                    }
                    std::get<0>(*cur).emplace_back(val);
                }
                /* skip , */
            }

            return ret;
        }

        res_t check_list(const vvi_t &l, const vvi_t &r)
        {
            /* rules: if both are integers, compare them.
             * - l<r, return true
             *   l==r, continue
             *   l>r, return false
             *
             * if both are lists, comapre the first value of each list the same way.
             * if left list runs out of items first, return pass.
             * if right list runs out of items first, return fail.
             *
             * if one value is integer, and one is list, make the integer a list of 1 */
            int i, j;
            res_t ret;
            for(i=0, j=0; i<l.size()&&j<r.size(); ++i, ++j) {
                if(std::holds_alternative<vvi_t>(l[i].v)&&std::holds_alternative<vvi_t>(r[j].v)) {
                    /* both are lists, so recurse into them */
                    ret = check_list(std::get<0>(l[i].v), std::get<0>(r[j].v));
                    if(ret!=R_CONTINUE) return ret;
                }
                else if(std::holds_alternative<element_t>(l[i].v)&&std::holds_alternative<element_t>(r[j].v)) {
                    /* both are integers */
                    auto li = std::get<1>(l[i].v);
                    auto ri = std::get<1>(r[i].v);

                    if(li<ri) return R_DONE_PASS;
                    if(ri<li) return R_DONE_FAIL;
                    /* if equal, continue */
                }
                else {
                    /* one is list, one is integer */
                    /* to check this, we are supposed to convert the single integer to a list, and run the check */
                    /* so which is the single number? */
                    vvi_t nl;
                    if(std::holds_alternative<element_t>(l[i].v)) {
                        /* left side is integer */
                        nl.emplace_back(l[j].v);
                        ret = check_list(nl, std::get<0>(r[j].v));
                        if(ret!=R_CONTINUE) return ret;
                    }
                    else {
                        /* right side is integer */
                        nl.emplace_back(r[i].v);
                        ret = check_list(std::get<0>(l[i].v), nl);
                        if(ret!=R_CONTINUE) return ret;
                    }
                }
            }

            /* at this point, we haven't had a failure (false) from any invocation, but if
             * the right side ran out of items first, it failed */
            if((j==r.size())&&(i<l.size())) return R_DONE_FAIL;
            /* and if left side ran out first, it passes */
            else if((i==l.size())&&(j<r.size())) return R_DONE_PASS;
            return R_CONTINUE;
        }

        bool operator==(const vi_t &l, const vi_t &r)
        {
            return l.v==r.v;
        }
    }
}
