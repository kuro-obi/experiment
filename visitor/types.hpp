#ifndef TYPES_HPP
#define TYPES_HPP
#include <vector>

struct Trader
{
};

struct Model
{
    std::vector<Trader*> traders_;
    void add(Trader* t)
    {
        traders_.push_back(t);
    }
};
struct Desk
{
    std::vector<Model*> models_;
    void add(Model* t)
    {
        models_.push_back(t);
    }
};

#endif
