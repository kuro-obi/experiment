#ifndef TYPES_HPP
#define TYPES_HPP
#include <type_traits>

template<typename IsBid, typename Price, typename Qty, typename ID>
struct Quote
{
    using is_bid_ty = IsBid;
    Price price_;
    Qty qty_;
    ID  id_;
};

using BidQuote = Quote<std::true_type, double, double, long>;
using AskQuote = Quote<std::false_type, double, double, long>;



#endif
