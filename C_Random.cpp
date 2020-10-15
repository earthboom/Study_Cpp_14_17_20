#include "stdafx.h"
#include <random>

int main(void)
{
    std::random_device RD;

    std::mt19937 generate(RD());

    std::uniform_int_distribution<int> distribute(0, 99);

    for(int i=0; i<5; ++i)
        std::cout << "Random number : " << distribute(generate) << std::endl;

    return 0;
}