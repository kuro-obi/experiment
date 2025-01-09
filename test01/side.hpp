#ifndef SIDE_HPP
#define SIDE_HPP
#include <memory>
#include <map>
#include "types.hpp"

template<typename IsBid, typename Price, typename Qty, typename ID>
struct Side
{
    using Compare = std::conditional<IsBid::value, std::less<Price>, std::greater<Price>>::type;
    using QuoteTy = Quote<IsBid, Price, Qty, ID>;
    using QuotePtr = std::unique_ptr< QuoteTy >;
    using Impl = std::multimap<Price, QuotePtr, Compare > ;

    Impl side_;


    void add( Price&& price, Qty&& qty, ID&& id)
    {
        auto q = std::make_unique<QuoteTy>( QuoteTy{price, qty, id});
        side_.insert( std::make_pair(price, std::move(q)));
    }

    void remove(ID&& id)
    {
        for(auto q : side_)
        {
            if(q.second->id_ == id )
            {
                side_.erase(q);
                return;
            }
        }
    }


    auto begin()
    {
        return side_.begin();
    }
    const auto cbegin()
    {
        return side_.cbegin();
    }

    auto end()
    {
        return side_.end();
    }
    const auto cend()
    {
        return side_.cend();
    }


};

#endif

