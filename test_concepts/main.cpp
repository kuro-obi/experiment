#include "Subs.hpp"
#include <iostream>

struct Listener
{
    void update_mid(double x)
    {
        std::cout<<x<<std::endl;
    }

};


void test_1()
{
    Subs<Listener> subs;
    subs.add(new Listener());

    subs.fire(1.2);

    auto f = subs.first();
    std::cout<< "IsRef:"<< std::is_reference<decltype(f)>::value<<std::endl;
}

int main(int argc, const char* argv[])
{
    test_1();
}

