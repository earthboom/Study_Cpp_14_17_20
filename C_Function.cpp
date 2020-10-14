#include "stdafx.h"
#include <functional>

int vsFunc(const std::string& _str)
{
    std::cout << "vsFunc Call! " << _str << std::endl;
    return 0;
}

struct funcStruct
{
    void operator()(char c){ std::cout << "funcStruct Call! " << c << std::endl; }
};

class funcClass
{
private:
    int iC;

public:
    funcClass(int _c) : iC(_c){}

    int function_fc(void)
    {
        std::cout << "Variable Function : " << ++iC << std::endl;
        return iC;
    }

    int const_function_fc(void) const
    {
        std::cout << "Constant Function : " << iC << std::endl;
        return iC;
    }
};

void add(int _x, int _y){ std::cout << _x << " + " << _y << " = " << _x + _y << std::endl; }
void subtract(int _x, int _y){ std::cout << _x << " - " << _y << " = " << _x - _y << std::endl; }

struct funcCallStruct
{
    int iData;

    funcCallStruct(int _i) : iData(_i) { std::cout << "General Constructor Call!" << std::endl; }
    funcCallStruct(const funcCallStruct& _s)
    {
        std::cout << "Copy Constructor Call!" << std::endl;
        iData = _s.iData;
    }

    funcCallStruct(funcCallStruct&& _s)
    {
        std::cout << "Move Constructor Call!" << std::endl;
        iData = _s.iData;
    }
};

void function_bind_test(funcCallStruct& f1, const funcCallStruct& f2){ f1.iData = f2.iData + 3; }

int main(void)
{
    std::function<int(const std::string&)> f1 = vsFunc;
    std::function<void(char)> f2 = funcStruct();
    std::function<void()> f3 = [](){ std::cout << "Function3 Call!" << std::endl; };

    f1("Skill Function!");
    f2('T');
    f3();

    funcClass pFC(1263);
    std::function<int(funcClass&)> f4 = &funcClass::function_fc;
    std::function<int(const funcClass&)> f5 = &funcClass::const_function_fc;

    f4(pFC);
    f5(pFC);


    std::vector<int> a(1);
    std::vector<int> b(2);
    std::vector<int> c(3);
    std::vector<int> d(4);

    std::vector<std::vector<int>> conVec;
    conVec.emplace_back(a);
    conVec.emplace_back(b);
    conVec.emplace_back(c);
    conVec.emplace_back(d);

    //std::transform의 4번째 매개변수에 기존 std::vector<int>::size를 넣으면, 오류가 발생한다.
    //std::transform 함수 내에서, 호출하는 문제.

    //해결책 1번 : std::function 이용.
    //std::function<size_t(const std::vector<int>&)> size_func = &std::vector<int>::size;

    std::vector<int> size_vec(4);
    std::transform(conVec.begin(), conVec.end(), size_vec.begin(),
                    //size_func); //해결책 1번
                    //std::mem_fn(&std::vector<int>::size));//해결책 2번 (std::mem_fn 함수는 functinon객체로 만들어줌.)
                    [](const auto& v){return v.size(); });//해결책 3번 람다함수

    for(auto& itr : size_vec)
        std::cout << "Vector size : " << itr << std::endl;


    
    // std::bind
    // 인자를 특정한 값으로 지정할 수 있다.
    auto add_func = std::bind(add, 10, std::placeholders::_1);   //첫번째 인자를 10으로 bind(고정)
    add_func(30);
    add_func(20, 50);   //2번째 인자는 무시된다.

    auto subtract_func_1 = std::bind(subtract, std::placeholders::_1, 11);  // 2번째 인자를 고정한다.
    auto subtract_func_2 = std::bind(subtract, std::placeholders::_2, std::placeholders::_1); //1번째, 2번째 인자의 순서 변경

    subtract_func_1(88);       // 88 - 11
    subtract_func_2(44, 77);   // 77 - 44



    funcCallStruct fcs1(10), fcs2(20);

    std::cout << "Before : " << fcs1.iData << std::endl;
    
    // std::ref 함수는 인자를 복사 가능한 레퍼런스로 변환해 줌.
    auto bindfunction = bind(function_bind_test, std::ref(fcs1), std::placeholders::_1);
    bindfunction(fcs2);

    std::cout << "After : " << fcs1.iData << std::endl;

    return 0;
}