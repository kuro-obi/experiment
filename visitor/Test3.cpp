#include <iostream>
#include "types.hpp"
#include <type_traits>
#include <tuple>

struct BaseRiskVisitor
{
    void visit(const Trader& trader)
    {
        std::cout<<"BaseRiskVisitor::visit trader"<<std::endl;
    }
    void visit(const Model& model)
    {
        std::cout<<"BaseRiskVisitor::visit model"<<std::endl;
    }
    void visit(const Desk& desk)
    {
        std::cout<<"BaseRiskVisitor::visit desk"<<std::endl;
    }
};

struct DefaultRiskVisitor 
{
    void visit(const Trader& trader)
    {
        std::cout<<"DefaultRiskVisitor::visit trader"<<std::endl;
    }
    void visit(const Model& model)
    {
        std::cout<<"DefaultRiskVisitor::visit model"<<std::endl;
        for(const auto& trader : model.traders_)
        {
            this->visit(*trader);
        }
    }
    void visit(const Desk& desk)
    {
        std::cout<<"DefaultRiskVisitor::visit desk"<<std::endl;
        for(const auto& model : desk.models_)
        {
            this->visit(*model);
        }
    }
};

struct LoggingRiskVisitor 
{

    void visit(const Trader& trader)
    {
        std::cout<<"LoggingRiskVisitor::visit trader"<<std::endl;
    }
    void visit(const Model& model)
    {
        std::cout<<"LoggingRiskVisitor::visit model"<<std::endl;
        for(const auto& trader : model.traders_)
        {
            this->visit(*trader);
        }
    }
    void visit(const Desk& desk)
    {
        std::cout<<"LoggingRiskVisitor::visit desk"<<std::endl;
        for(const auto& model : desk.models_)
        {
            this->visit(*model);
        }
    }
};

struct A {};
struct B {};
struct C {};

template<typename ...T>
struct VisitorDriver : public T ... 
{
    typedef std::tuple<T...> base_types;

    template<size_t N, typename F>
    requires ( N >= std::tuple_size<base_types>{})
    void for_each_base_i(F&& func)
    {
    }

    template<size_t N, typename F>
    requires ( N < std::tuple_size<base_types>{})
    void for_each_base_i(F&& func)
    {
        typedef typename std::tuple_element<N,base_types>::type base_ty;
        func( static_cast<base_ty*>(this)   );
        for_each_base_i<N+1>(std::forward<F>(func));
    }

    template<typename F>
    void for_each_base(F&& func)
    {
        typedef typename std::tuple_element<0,base_types>::type base_ty;
        func( static_cast<base_ty*>(this)   );
        for_each_base_i<1>(std::forward<F>(func));
    }


    VisitorDriver()
    {
        typedef decltype(*this) this_type;
        std::cout<<"VisitorDriver:"<< typeid(this_type).name()  <<" bases: "<< std::tuple_size<base_types>{} <<std::endl;
        for_each_base([](const auto b){ std::cout<<" base_type: "<< typeid(b).name() << std::endl;});
    }


    void visit(const Trader& trader)
    {
        for_each_base([&trader] (auto* b) { b->visit(trader);});
    }
    void visit(const Model& model)
    {
        for(const auto& trader : model.traders_)
        {
            this->visit(*trader);
        }
        for_each_base([&model] (auto* b) { b->visit(model);});
    }
    void visit(const Desk& desk)
    {
        for(const auto& model : desk.models_)
        {
            this->visit(*model);
        }
        for_each_base([&desk] (auto* b) { b->visit(desk);});
    }

};


void test_1()
{
    
    Desk desk;
    Model model;
    Trader trader;

    model.add(&trader);
    desk.add(&model);

    VisitorDriver<DefaultRiskVisitor,LoggingRiskVisitor> visitor; 
    visitor.visit(desk);

}


int main(int argc, const char* argv[])
{
    test_1();
}


