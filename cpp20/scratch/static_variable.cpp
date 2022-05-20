#include <iostream>

template<typename T>
struct Test
{
    static size_t id_;
    template<typename ... Args>
    Test(Args&& ...)
    {
        ++id_;
        std::cout<<"Test(Args..)::"<<id_<<std::endl;
    }

    Test()
    {
        ++id_;
        std::cout<<"Test()::"<<id_<<std::endl;
    }

};

template<typename T> size_t Test<T>::id_ = 0;

int main(int argc, const char* argv[])
{
    Test<int> b;
    std::cout<<Test<int>::id_<<std::endl;
    Test<int> c;
    Test<double> d;


    std::cout<<Test<int>::id_<<std::endl;
    std::cout<<Test<double>::id_<<std::endl;
    std::cout<<Test<std::string>::id_<<std::endl;
    std::cout<<Test<std::string&&>::id_<<std::endl;
}