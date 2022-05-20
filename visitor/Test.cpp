#include <iostream>
#include "types.hpp"

template<typename T>
struct RiskVisitor{};

template<typename T>
struct DefaultRiskVisitor : public RiskVisitor<T>
{

    void visit(const Trader& trader)
    {
    }
    void visit(const Model& model)
    {
    }
    void visit(const Desk& desk)
    {
        std::cout<<"visiting desk"<<std::endl;
    }
};

template<typename T>
struct LoggingRiskVisitor : public DefaultRiskVisitor<T>
{

    void visit(const Trader& trader)
    {
    }
    void visit(const Model& model)
    {
    }
    void visit(const Desk& desk)
    {
        std::cout<<"visiting desk"<<std::endl;
    }
};



void test_1()
{
    DefaultRiskVisitor<RiskVisitor> def_visitor;
    
    Desk desk;
    Model model;
    Trader trader;

    model.add(&trader);
    desk.add(&model);

    def_visitor.visit(desk);


}
