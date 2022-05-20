#include "Node.hpp"
#include <iostream>

class Solution {


    public:
    bool hasCycle(ListNode *head) 
    {   
        int n = 0;
        if( head == nullptr or head->next==nullptr)
        {        
            return false;
        }
        auto slow = head;
        auto fast = head->next;
        while(fast!=slow and slow != nullptr and fast!=nullptr)
        {
            ++n;
            slow = slow->next;
            if(fast->next)
            {
                fast = fast->next->next;
            }
            else
            {
                fast = nullptr;
            }
        }
        std::cout<<"N:"<<n<<std::endl;
        return fast==slow;
    }
};


int main(int argc, const char* argv[])
{
    ListNode* head = new ListNode(3);
    append(head, 2,0,-4);
    ListNode* tail = last(head);
    tail->next = head;  
    //print(head);
    //print(tail);
    
    Solution sol;
    std::cout<<"Has Cycle:"<<sol.hasCycle(head)<<std::endl;
}
