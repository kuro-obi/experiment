#include <iostream>

void foo(bool test)
{
    if(test) [[likely]]
    {
        std::cout<<"Test is true"<<std::endl;
    }
    else
    {
        std::cout<<"Test is false"<<std::endl;
    }
}


int main(int argc, const char* argv[])
{
    std::cout<<"hello!"<<std::endl;
}


