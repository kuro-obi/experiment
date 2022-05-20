#include <iostream>
#include <cc_concepts.hpp>
#include <Book.hpp>
#include <memory>
#include <type_traits>

namespace cc{

template<typename L>
requires cc::BookListener<L>
struct Book
{
    L& l_;
    Book(L& l): l_(l)
    {}

    void foo()
    {
        l_.template on_update<Event>();
    }
    void bar()
    {
        l_.template on_update<OnAdd>();
    }
};



}

struct Listener
{
    template<typename Ev>
    void on_update()
    {
        std::cout<<"Listener::on_update()"<<typeid(Ev).name()<<std::endl;
    }
};


int main(int argc, const char* argv[])
{
    cc::Quote<true> q{100.5, 5};
    std::cout<<price(q)<<std::endl;
    std::cout<<price(&q)<<std::endl;
    std::cout<<"Qty:"<<qty(q)<<std::endl;
    std::cout<<"Side:"<<side(q)<<std::endl;

    
    Listener listener;
    cc::Book<Listener> book(listener);
    book.foo();
    book.bar();

    std::cout<<"trivial construct:"<< std::is_trivially_constructible<cc::Quote<true>>() << std::endl;
    std::cout<<"trivial construct:"<< std::is_trivially_constructible<cc::Quote<true,std::string>>() << std::endl;

}

