#include "stdafx.h"
#include <tuple>

//tuple 반환값을 tie로 대체 가능
std::tuple<int&, int&> GetMinMiax(int& _a, int& _b)
{
    if(_a > _b)
        return std::tie(_a, _b);
    else
        return std::tie(_b, _a);    
}

int main(void)
{
    std::cout << " TUPLE " << std::endl;

    std::tuple<int, double, std::string> _t1 = std::make_tuple(32, 3123.53135f, "TUPLE");
    std::cout << std::get<0>(_t1) << ", " << std::get<1>(_t1) << ", " << std::get<2>(_t1) << std::endl;

    
    auto _t2 = std::make_tuple(32, "HOW ARE YOU", 'P');
    std::cout << std::get<0>(_t2) << ", " << std::get<1>(_t2) << ", " << std::get<2>(_t2) << std::endl;

    
    auto _t3 = std::make_tuple(315.1342, 9385, '&', "All is well", 21.315);
    float _a = 0.0f;
    int _b = 0, _e = 0;
    char _c;
    std::string _d;

    //std::tie를 이용하여 tuple 데이터 한 번에 받기
    std::tie(_a, _b, _c, _d, _e) = _t3;
    std::cout << _a << ", " << _b << ", " << _c << ", " << _d << ", " << _e << std::endl;

    //std::ignore을 이용해, 받고 싶지 않은 데이터를 골라내기
    _a = 0.0f, _b = 0, _c = NULL, _d = "", _e = 0;
    std::tie(_a, std::ignore, _c, _d, std::ignore) = _t3;
    std::cout << _a << ", " << _b << ", " << _c << ", " << _d << ", " << _e << std::endl;

    // 구조화된 바인딩을 이용
    auto [va, vb, vc, vd, ve] = _t3;
    std::cout << va << ", " << vb << ", " << vc << ", " << vd << ", " << ve << std::endl;

    int ia = 32624, ib = 43024;
    auto [ma, mb] = GetMinMiax(ia, ib);
    std::cout << ma << ", " << mb << std::endl;

    return 0;
}