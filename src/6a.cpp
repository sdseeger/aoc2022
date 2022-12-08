#include <iostream>
#include <span>

int main()
{
    std::string s;
    std::getline(std::cin, s);
    std::span sp{s};
    const auto sz = s.size();
    int i;

    for(i=0; (i+4)<sz; ++i) {
        auto sp_ = sp.subspan(i, 4);
        if(sp_[0]==sp_[1]) continue;
        if(sp_[0]==sp_[2]) continue;
        if(sp_[0]==sp_[3]) continue;
        if(sp_[1]==sp_[2]) continue;
        if(sp_[1]==sp_[3]) continue;
        if(sp_[2]==sp_[3]) continue;
        std::cout << sp_[0] << ' ' << sp_[1] << ' ' << sp_[2] << ' ' << sp_[3] << std::endl;
        break;
    }

    std::cout << i+4 << std::endl;
    return 0;
}
