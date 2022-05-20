#ifndef CC_CONCEPTS_HPP
#define CC_CONCEPTS_HPP
#include <concepts>
namespace cc {

    template <typename T>
    concept IsQuote = requires (T&& x)
    {
        x.price();
        x.qty();
        x.side();
    };

    struct Event {}; 
    struct OnAdd : Event {};

    template<typename L>
    concept BookListener = requires(L&& l)
    {
        l.template on_update<Event>();

    };

    template <typename S>
    concept SideInterface = requires(S&& s)
    {
        s.begin();
        s.end();
    };

    template<typename B>
    concept BookInterface = requires(B&& l)
    {
        l.template side<std::true_type>();
        l.template side<std::false_type>();
    };

    template<typename T>
    concept BookBuilderInterface = requires(T& l) 
    {
        l.template book();
    };

}

#endif