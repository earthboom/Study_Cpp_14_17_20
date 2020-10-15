#include "stdafx.h"

// constexpr
// C++ 11 도입
// 컴파일 시간 상수로 컴파일 시간에 초기값을 확인할 수 있는 상수.
// define을 대체할 수 있음.
// 초기값을 넣지 않으면 오류 발생!

constexpr float PI = 3.141592f;
constexpr float A = {1000};
constexpr float B = exp(5);

//constexpr int C //초기값을 넣지 않아 에러.

//int _d = 100; // 상수가 아니면 안됨.
const int _d = 100;
constexpr int D = _d + 1000;  

template<typename T, int N>
constexpr int Length(const T(&)[N]){ return N; }

constexpr int Factorial(int _n){ return _n == 1 ? 1 : _n * Factorial(_n-1); }

class defClass
{
private:
    int iNum;

public:
    constexpr explicit defClass(int _i) : iNum(_i){}
    constexpr int GetValue(void) const { return iNum; }
};

int main(void)
{
    std::cout << "PI = " << PI << std::endl;
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "D = " << D << std::endl;

    const int nums[]{1, 2, 3, 4, 5};
    std::cout << Length(nums) << std::endl;

    std::cout << "Factorial : " << Factorial(6) << std::endl;

    constexpr defClass testClass(100);  //testClass는 상수가 됨.
    //testClass = defClass(200);  //error
    
    std::cout << "Value : " << testClass.GetValue() << std::endl;

    return 0;
}