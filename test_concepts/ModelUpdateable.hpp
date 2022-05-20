#ifndef MODEL_UPDATEABLE_HPP
#define MODEL_UPDATEABLE_HPP

template <typename T>
concept ModelUpdateable = requires(T t)
{
    { t.update_mid(1.0)};
};


#endif

