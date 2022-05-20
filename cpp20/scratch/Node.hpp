#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr){}
};

void append(ListNode* head, int val)
{
    while(head->next != nullptr)
    {
        head = head->next;
    }
    head->next = new ListNode(val);
}

void print(ListNode* head)
{
    while(head!=nullptr)
    {
        std::cout<<head->val<<",";
        head=head->next;
    }
    std::cout<<std::endl;
}

void append(ListNode* h){}

template<typename ... Args>
void append(ListNode* head, int val, Args&& ... params)
{
    append(head,val);
    append(head, std::forward<Args>(params)...);
}

ListNode* last(ListNode* begin)
{
    while( begin->next != nullptr)
    {
        begin = begin->next;
    }
    return begin;
}

#endif
