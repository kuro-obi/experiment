#ifndef BOOK_HPP
#define BOOK_HPP
#include "side.hpp"
#include <memory>
#include <map>


template<typename Price, typename Qty, typename ID>
struct Book
{

    using BidSide = Side<std::true_type, Price, Qty, ID>;
    using AskSide = Side<std::false_type, Price, Qty, ID>;
    
    BidSide bid_;
    AskSide ask_;

    template<bool IsBid>
    auto& side() 
    {
        if constexpr(IsBid)
        {
            return bid_;
        }
        else
        {
            return ask_;
        }
    }

    template<bool IsBid>
    const auto& side() const
    {
        if constexpr(IsBid)
        {
            return bid_;
        }
        else
        {
            return ask_;
        }
    }

    template<typename IsBid>
    const auto& side() const 
    {
        return side<IsBid::value>();
    }

    template<typename IsBid>
    auto& side() 
    {
        return side<IsBid::value>();
    }

    const auto& bid() const { return side<true>(); }
    const auto& ask() const { return side<false>(); }

    template<typename IsBid>
    void add(Price&& price, Qty&& qty, ID&& id)
    {
        side<IsBid>().add(std::move(price), std::move(qty), std::move(id));
    }

};

#endif

