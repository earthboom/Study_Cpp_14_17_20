#include "stdafx.h"
#include <chrono>
#include <ctime>
#include <random>
#include <iomanip>

namespace ch = std::chrono;

int main(void)
{
    std::random_device rd;
    std::mt19937 mtGen(rd());

    std::uniform_int_distribution<> uniform_dis(0, 1000);

    for(int i=1; i<=1000000; i*=10)
    {
        std::vector<int> vecRandNum;
        vecRandNum.reserve(i);

        //std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        ch::time_point<ch::high_resolution_clock> start = ch::high_resolution_clock::now();

        for(int j=0; j<i; ++j)
            vecRandNum.emplace_back(uniform_dis(mtGen));
        
        //std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        ch::time_point<ch::high_resolution_clock> end = ch::high_resolution_clock::now();

        auto diff = end - start;  
        //std::chrono::duration diff = end - start;     //C++17 이후
        //ch::duration diff = end - start;

        std::cout << std::setw(7) << "When generating " << i << " random number, tick : " << diff.count() << std::endl;
        
        // std::chrono::microseconds : 1초에 10^6의 틱.
        std::cout << std::setw(7) << "When generating " << i << " random number, time : " << ch::duration_cast<ch::microseconds>(diff).count() << "us" << std::endl;
    }

    
    auto now = ch::system_clock::now();
    std::time_t t = ch::system_clock::to_time_t(now);

    std::cout << "now time : " << std::put_time(std::localtime(&t), "%F %T %z") << std::endl;

    return 0;
}