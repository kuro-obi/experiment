#include <iostream>

struct Base
{
    
    void foo()
    {
        std::cout<<"Base::foo()"<<std::endl;
    }
    virtual void bar()
    {
        std::cout<<"Base::bar()"<<std::endl;
    }

};

struct Derived1 : Base
{
    void foo()
    {
        std::cout<<"Derived1::foo()"<<std::endl;
    }
    void bar()
    {
        std::cout<<"Derived1::bar()"<<std::endl;
    }
};


int main(int argc, const char* argv[])
{
    Derived1 d;
    d.foo();
    d.bar();


    Base* b = &d;
    b->foo();
    b->bar();

}
