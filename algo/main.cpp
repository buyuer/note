#include "algo.hpp"

template <typename T> SingleLinkNode<T>* reversal1(SingleLinkNode<T>* head)
{
    if (head and not head->next) {
        return head;
    }

    auto last = reversal(head->next);
    head->next->next = head;
    head->next = nullptr;
    return last;
}

template <typename T> SingleLinkNode<T>* reversal2(SingleLinkNode<T>* head)
{
    SingleLinkNode<T>* p = head;
    SingleLinkNode<T>* last = nullptr;
    while (p) {
        auto temp = p->next;
        p->next = last;
        last = p;
        p = temp;
    }

    return last;
}

int main()
{
    auto head = Node::create({ 1, 2, 3, 4 });
    head->print();
    head = reversal2(head);
    head->print();
    delete head;
}