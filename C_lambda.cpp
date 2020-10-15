#include "stdafx.h"
#include <functional>

// Lambda

// []()->{}()

// [] : introducer(개시자)
// 외부변수를 넣으면, 람다함수가 이를 캡처하여, 내부에서 사용이 가능하게 함.
// 생략이 불가능

// [&] : 외부의 모든 변수들을 레퍼런스로 가져옴 (call by reference)
// [=] : 외부의 모든 변수들을 값으로 가져옴 (call by value)

// [=, &x, &y] / [&, x, y] : 외부 모든 변수를 값/레퍼런스로 가져오고, x, y만 레퍼런스/값으로 가져온다. 

// () : parameter(인자)
// 람다가 실행시 받을 인자들(평소 함수의 인자를 생각하면 됨.)
// 넣을 인자가 없다면 생략이 가능하다.

// -> : return type(반환 타입)
// 람다 함수가 종료되고 반환될 타입. 없다면 생략 가능.

// {} : statement(실제 동작)
// 실제 람다 함수의 동작.

// () : 실제 들어갈 인자의 값.
// 필요 인자가 없다면, 비워둬도 된다. 
// 호출을 한다면 반드시 써야함. 

template<typename T>
void Fill(std::vector<int>& _v, T _func)
{
    int i = 0;
    while(!_func())
    {
        _v.emplace_back(i++);
    }
}

class testClass1
{
private:
    std::vector<int> vecValue;
    int m_iNum;

public:
    testClass1(int _i) : m_iNum(_i){}

    testClass1& put(int _i)
    {
        vecValue.emplace_back(_i);
        return *this;
    }

    int Extras(void)
    {
        int count = 0;
        
        //class의 맴버변수를 캡처하면, 암묵적으로 this가 캡처된다 (this-> 가 생략된 샘.)
        for_each(vecValue.begin(), vecValue.end(), 
                [=, &count](int _v){ count += _v % m_iNum; });

        return count;
    }
};

struct testStruct1
{
    testStruct1() : iNum(8){} 
    void capNumChange()
    {   
        // 보통 캡처된 변수는 상수가 되어 변경이 불가하지만,
        // 여기선, this를 캡처하여, this->iNum을 변경하기 때문에, mutable없이도 변경 가능하다.
        // this 를 변경한 것이 아니기 때문.
        [=]{ iNum *= 10 ;}();
    }

    int iNum;
};

struct CallTrace
{
    CallTrace(void) : iNum(0) { std::cout << "Constructor \n"; }
    CallTrace(CallTrace const&) { std::cout << "Copy Constructor \n"; }
    ~CallTrace(void) { std::cout << "Destroy \n"; }

    CallTrace& operator=(CallTrace&)
    {
        std::cout << "assign\n";
        return *this;
    }

    int iNum;
};

int main(void)
{
    // 뒤에 ()를 붙이면 호출되어 실행됨.
    [](){std::cout << "Hello, Lambda!" << std::endl;}();

    int num1 = 5;
    [](int& _i)->int{
        int ri = _i * 2;
        std::cout << ri << std::endl;
        return ri;
    }(num1);



    std::vector<int> vecCardi;
    vecCardi.emplace_back(1);
    vecCardi.emplace_back(2);
    vecCardi.emplace_back(3);
    vecCardi.emplace_back(4);

    for_each(vecCardi.begin(), vecCardi.end(), [&](int i){ num1 += i; });

    std::cout << "number : " << num1 << std::endl;




    std::vector<int> vecStuff;
    Fill(vecStuff, [&]()->bool{return vecStuff.size() >= 10; });

    for_each(vecStuff.begin(), vecStuff.end(), [](int& i){ std::cout << i << " ";});
    std::cout << std::endl;


    vecStuff.clear();

    Fill(vecStuff, [&]()->bool{
        int _sum = 0;
        for_each(vecStuff.begin(), vecStuff.end(), [&](int& _i){ _sum += _i;});
        return _sum >= 100;
    });
    for_each(vecStuff.begin(), vecStuff.end(), [](int& i){std::cout << i << " ";});

    std::cout << std::endl;

    // 캡처 타이밍.
    int iCapture = 3000;
    auto capFunc = [=](){std::cout << iCapture << std::endl;};  //람다함수가 생성하는 타이밍에 캡처됨.
    iCapture = 3;
    capFunc();


    int iCapture2 = 2000;
    //auto capFunc2 = [=]()->int{ return iCapture2 *= 2; }; // 캡처된 변수는 자동으로 상수가 되어 변경이 불가하다.
    auto capFunc2 = [=]()mutable->int{ return iCapture2 *= 2; }; //mutable 키워드를 추가하면 변경이 가능하다.
    std::cout << capFunc2() << std::endl;
    
    

    testClass1 tc(10);
    tc.put(123).put(32).put(313103);
    std::cout << "extras : " << tc.Extras() << std::endl;    

    testStruct1 ts;
    ts.capNumChange();
    std::cout << "struct capture value change : " << ts.iNum << std::endl;


    // 캡처의 범위
    // 첫번째 람다에서 cp1을 캡처하지 않아서, 두번째 람다에서는 cp1의 값을 알 수 없어 에러가 발생함.
    // int cp1 = 44;
    // auto cpfunc = [](){
    //     int cp2 = 88;
    //     auto cpinfunc = [=]{std::cout << cp2 / cp1;};
    //     cpinfunc();
    // };
    // cpfunc();


    CallTrace CT;
    int iCT = 326;

    auto FCT1 = [=]{ int i = CT.iNum; };

    std::cout << "==== make copy ====" << std::endl;

    auto FCT2 = FCT1;


    // typdef 반환값 자료형 (*함수포인터 별칭)(매개변수 자료형....)
    typedef int (*f_type)(int);
    f_type f = [](int i)->int{ return i + 500; };
    std::cout << f(500) << std::endl;


    std::function<int(std::string const&)> fff = [](std::string const& str)->int{ return str.size(); };
    std::cout << fff("www.google.co.kr") << std::endl;

    return 0;
}