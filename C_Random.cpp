#include "stdafx.h"
#include <iomanip>
#include <random>

int main(void)
{
    // 시드값을 얻기 위한 device 생성
    // 운영체제에서 제공하는 난수 사용 가능.
    std::random_device RD;

    // random device를 통해 난수 엔진을 초기화
    // mt19937 메르센 트위스터 알고리즘 사용 (다른 엔진 객체 : minstd_rand)        
    std::mt19937 generate(RD());

    // 0 ~ 99까지 균등하게 나타나는 난수열을 생성하기 위한 균등 분포 정의
    // 균등분포 객체
    std::uniform_int_distribution<int> distribute(0, 99);

    // 균등 분포 객체에 난수 엔진 객체를 전달함으로서, 난수 생성.
    for(int i=0; i<5; ++i)
        std::cout << "Random number : " << distribute(generate) << std::endl;



    std::normal_distribution<double> normal_dis(0, 1);

    std::map<int, int> nd_map{};
    for(int i=0; i<10000; ++i)
        ++nd_map[std::round(normal_dis(generate))]; //round(x) : x의 반올림 함수
    
    // setw(x) : x만큼의 공간을 확보한 뒤에 문자를 출력
    for(auto _i : nd_map)
        std::cout << std::setw(10) << _i.first << ", " << std::string(_i.second / 100, '*') << _i.second << std::endl;

    

    return 0;
}