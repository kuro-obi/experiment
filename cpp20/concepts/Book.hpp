#ifndef CC_BOOK_HPP
#define CC_BOOK_HPP
#include <iostream>
#include <cc_concepts.hpp>
#include <memory>
#include <type_traits>

namespace cc{

template<bool IsBid, typename ID = unsigned long>
struct Quote
{
    static constexpr bool side_ = IsBid;
    double price_;
    double qty_;
    ID id_;
    //Quote(double px, double q): price_(px), qty_(q){}
    constexpr auto side() const { return side_; }
    double price() const { return price_; }
    double qty() const { return qty_;}
    const ID& id() const { return id_; }

    //Quote(const Quote<IsBid>& q)
    //{
    //    price_ = q.price_;
    //    qty_   = q.qty_;
    //    std::cerr<<"copy ctor"<<std::endl;
    //}

    //const Quote& operator=(const Quote<IsBid>& q)
    //{
    //    std::cerr<<"operator="<<std::endl;
    //    if(this != &q)
    //    {
    //        price_ = q.price_;
    //        qty_   = q.qty_;
    //    }
    //    return *this;
    //}
};

template<typename T>
requires IsQuote<typename std::remove_pointer<T>::type> && std::is_pointer<T>::value
double price(T&& t)
{
    std::cout<<"is_pointer: "<< std::is_pointer<T>::value << std::endl;
    return t->price();
}

template<typename T>
requires IsQuote<T>
double price(T&& t)
{
    return t.price();
}

template<typename T>
double qty(T&& t) requires IsQuote<T>
{
    return t.qty();
}
template<IsQuote T>
double side(T&& t) 
{
    return t.side();
}

}
#endif

