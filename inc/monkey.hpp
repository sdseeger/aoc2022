#ifndef MONKEY__HPP
#define MONKEY__HPP

#include <vector>
#include <functional>
#include <cstdint>

namespace aoc {
    namespace monkey {
        template<typename T>
        struct monkey {
            using op_t = std::function<uint64_t(uint64_t)>;
            monkey(std::vector<T> &&iv, op_t &&op, int div, int throw_true, int throw_false):
                items(std::forward<std::vector<T>>(iv)), op(std::forward<op_t>(op)),
                div(div), throw_true(throw_true), throw_false(throw_false) {}

            virtual void receive_item(T &item) {
                items.emplace_back(item);
            }

            std::vector<T> items; /* it's not good oop, but let everyone use this */
            const op_t op;
            const int div; /* divisible */
            const int throw_true;
            const int throw_false;
        };

        template<typename T> std::vector<monkey<T>> parse(std::function<T(int)> &&fn)
        {
            std::vector<monkey<T>> monkeys;

            aoc::parse(std::cin, 7, [&](is_t is) {
                std::vector<T> vi;

                /* get the starting items */
                is[1].ignore(18); /*   Starting items: */
                while(!is[1].eof()) {
                    int val;

                    is[1] >> val;
                    vi.emplace_back(fn(val));
                    is[1].ignore(2);
                }

                /* build the operation */
                is[2].ignore(23); /*   Operation: new = old */
                char oper;
                typename monkey<T>::op_t op;
                is[2] >> oper;
                int operand;
                is[2] >> operand;
                /* if !is[2].fail(), then it's a number, otherwise "old" */
                if(!is[2].fail()) {
                    /* number */
                    if(oper=='+') {
                        op = [operand](uint64_t old) {
                            return old+operand;
                        };
                    }
                    else {
                        /* must be * */
                        op = [operand](uint64_t old) {
                            return old*operand;
                        };
                    }
                }
                else {
                    /* old */
                    /* NOTE: not sure if any input has old + old, but just handle it anyway */
                    if(oper=='+') {
                        op = [](uint64_t old) {
                            return old+old;
                        };
                    }
                    else {
                        /* must be * */
                        op = [](uint64_t old) {
                            return old*old;
                        };
                    }
                }

                /* get div */
                is[3].ignore(21); /*   Test: divisible by */
                int div;
                is[3] >> div;

                /* get throw_true */
                is[4].ignore(29); /*      If true: throw to monkey */
                int throw_true;
                is[4] >> throw_true;

                /* get throw_false */
                is[5].ignore(30); /*      If false: throw to monkey */
                int throw_false;
                is[5] >> throw_false;

                monkeys.emplace_back(std::move(vi), std::move(op), div, throw_true, throw_false);
            });

            return monkeys;
        }
    }
}
#endif
