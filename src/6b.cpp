#include <iostream>
#include <algorithm>
#include <span>
#include <vector>

#include <cstring>

int main()
{
    const char NUM_CHARS = 14;
    const char START_CHAR = 'a';
    const char STOP_CHAR = 'z';
    std::string s;
    std::getline(std::cin, s);
    std::span sp{s};
    const auto sz = s.size();
    int i;

    for(i=0; (i+NUM_CHARS)<sz; ++i) {
        auto sp_ = sp.subspan(i, NUM_CHARS);
        int count=0;
        uint8_t vb[128];
        memset(vb, 0, sizeof(vb));
        for(auto &c : sp_) vb[c] = 1;
        std::for_each(vb+START_CHAR, vb+STOP_CHAR+1, [&count](uint8_t &c) {
            count+=c;
        });
        if(count==NUM_CHARS) break;
    }

    std::cout << i+NUM_CHARS << std::endl;
    return 0;
}
