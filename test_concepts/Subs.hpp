#ifndef SUBS_HPP
#define SUBS_HPP

#include "ModelUpdateable.hpp"
#include <vector>

template<typename T>
requires ModelUpdateable<T>
struct Subs
{
    std::vector<T*> listeners_;

    Subs()
    {
    };

    void add(T* t)
    {
        listeners_.push_back(t);
    }

    void fire(double x)
    {
        for(auto& t: listeners_)
        {
            t->update_mid(x);
        }
    }

    auto& first() 
    {
        return *listeners_.front();
    }
};

#endif

