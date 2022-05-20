#include <iostream>

template<typename T, typename T2=T>
concept Subtractable = requires(T a, T2 b)
{
        a - b;
};

template<typename T, typename T2 = T>
concept Addable = requires(T a, T2 b)
{
        a + b;
};

template<typename T, typename T2 = T>
concept Dividable = requires(T a, T2 b)
{
        a/b;
};

template<typename T, typename T2 = T >
concept DivAddable = Addable<T,T2> && Dividable<T,T2>;

template<typename T>
void f(T x)
{
        if constexpr(Addable<T>){ /*...*/ }
        else if constexpr(requires(T a, T b) { a + b; }){ /*...*/ }
}

template<typename T>
requires Addable<T>
auto f1(T a, T b) requires Subtractable<T>; // Addable<T> && Subtractable<T>

auto l = []<typename T> requires Addable<T>
    (T a, T b) requires Subtractable<T>{};

template<typename T>
requires Addable<T>
class C;

// infamous `requires requires`. First `requires` is requires-clause,
// second one is requires-expression. Useful if you don't want to introduce new
// concept.
template<typename T>
requires requires(T a, T b) {a + b;}
auto f4(T x);


template<typename T>
concept Integral = std::integral<T>;

template<typename T>
concept Integral4 = std::integral<T> && sizeof(T) == 4;

// requires-clause also works here
template<template<typename T1> requires Integral<T1> typename T>
void f2(){}

// f() and f2() forms are equal
template<template<Integral T1> typename T>
void f(){
    f2<T>();
}

// unconstrained template template parameter can accept constrained arguments
template<template<typename T1> typename T>
void f3(){}

template<typename T>
struct S1{};

template<Integral T>
struct S2{};

template<Integral4 T>
struct S3{};

void test(){
    f<S1>();    // OK
    f<S2>();    // OK
    // error, S3 is constrained by Integral4 which is more constrained than
    // f()'s Integral
    //f<S3>();

    // all are OK
    f3<S1>();
    f3<S2>();
    f3<S3>();
}

template<typename T>
concept is_sortable = true;

auto l2 = [](auto x){};
void f1(auto x){}               // unconstrained template
void f2(is_sortable auto x){}   // constrained template

template<is_sortable auto NonTypeParameter, is_sortable TypeParameter>
is_sortable auto f3(is_sortable auto x, auto y)
{
    // notice that nothing is allowed between constraint name and `auto`
    is_sortable auto z = 0;
    return 0;
}

template<is_sortable auto... NonTypePack, is_sortable... TypePack>
void f4(TypePack... args){}

int f(){ return 1;}

// takes two parameters
template<typename T1, typename T2>
concept C2 = true;
// binds second parameter
C2<double> auto v = f(); // means C2<int, double>

struct X{
    operator is_sortable auto() {
        std::cerr<<"X::auto conversion"<<std::endl;
        return 0;
    }
};

auto f5() -> is_sortable decltype(auto){
    f4<1,2,3>(1,2,3);
    return new is_sortable auto(1);
}


template<typename T>
int counter(){
    static int value{};
    return value++;
}

inline int ff(){
     return counter<decltype([]{})>();
}


template<auto> struct S{ void call(){} };
// cast lambda to pointer
inline S<+[]{}> g_s;
//
//// a.cpp
////#include "a.h"
//auto v = ff();
//g_s.call();
//
//// b.cpp
////#include "a.h"
//auto v = ff();
//g_s.call();

auto sl = [](auto x){ static auto y = x; return ++y; };


struct Bf
{
    unsigned int b_ : 3;
};




int main(int argc, const char* argv[])
{
    auto z = f5();
    std::cout<< typeid(z).name() << std::endl;

    X x;
    int y = x;
    double w = x;

    std::cout<<counter<int>()<<std::endl;
    std::cout<<counter<int>()<<std::endl;
    std::cout<<counter<int>()<<std::endl;
    std::cout<<counter<int>()<<std::endl;

    std::cout<<ff()<<std::endl;
    std::cout<<ff()<<std::endl;
    std::cout<<ff()<<std::endl;
    std::cout<<ff()<<std::endl;

    g_s.call();
    g_s.call();
    std::cout<<ff()<<std::endl;

    std::cout<< sl(-3) << std::endl;
    std::cout<< sl(1) << std::endl;

    std::cout<<sl(1.55)<<std::endl;

    
    Bf bf{2};
    std::cout << bf.b_ << std::endl;


    std::cerr<<"exit"<<std::endl;
}
