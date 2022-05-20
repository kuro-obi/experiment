#include <iostream>
struct A
{
    int a_;
};

class B
{
    public:
    int b_;
};
int main(int argc, const char* argv[])
{
    int v;
    std::cout<<v<<std::endl;

    A a;
    std::cout<<a.a_<<std::endl;
    
    A a1(); //function declaration
    //std::cout<<a1.a_<<std::endl;

    std::cout<<A().a_<<std::endl;

    B b;
    std::cout<<b.b_<<std::endl;

    //B b1();
    //std::cout<<b1.b_<<std::endl;

    std::cout<<B().b_<<std::endl;
    int c;
    std::cout<<c<<std::endl;
}
