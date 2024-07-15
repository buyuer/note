#pragma once

#include <iostream>
#include <vector>

template <typename T> class SingleLinkList {
public:
    struct Node {
        T val {};
        Node* next {};

        ~Node() { delete next; }
    };

    explicit SingleLinkList<T>(const std::vector<T>& items)
    {
        node_ = create(items);
    }

    ~SingleLinkList() { delete node_; }

    void print() const { print(node_); }

    static void print(SingleLinkList<T>::Node* head)
    {
        auto p = head;
        std::cout << "[";
        while (p) {
            std::cout << p->val << ", ";
            p = p->next;
        }
        std::cout << "]" << std::endl;
    }

    static SingleLinkList<T>::Node* create(const std::vector<T>& items)
    {
        Node* head { nullptr };
        Node** p { &head };
        for (const auto& item : items) {
            *p = new Node { .val = item };
            p = &((*p)->next);
        }
        return head;
    }

    static SingleLinkList<T>::Node* reversal(SingleLinkList<T>::Node* head)
    {
        auto p = head;
        Node* last = nullptr;
        while (p) {
            auto temp = p->next;
            p->next = last;
            last = p;
            p = temp;
        }

        return last;
    }

    static SingleLinkList<T>::Node* reversal(SingleLinkList<T>::Node* start,
                                             SingleLinkList<T>::Node* end)
    {
        auto head = start;
        auto last = end->next;
        while (head not_eq end) {
            auto next = head->next;
            head->next = last;
            last = head;
            head = next;
        }
        head->next = last;
        return end;
    }

    static SingleLinkList<T>::Node* reversal(SingleLinkList<T>::Node* head,
                                             int start, int end)
    {
        Node* start_node {};
        Node* end_node {};
        Node** last { &head };
        int index = 0;
        auto p = head;
        while (p and index < start) {
            last = &(p->next);
            p = p->next;
            index += 1;
        }
        start_node = p;
        while (p and index < end) {
            p = p->next;
            index += 1;
        }
        end_node = p;

        *last = reversal(start_node, end_node);

        return head;
    }

    static SingleLinkList<T>::Node* reversal_(SingleLinkList<T>::Node* head)
    {
        if (head and not head->next) {
            return head;
        }

        const auto last = reversal_(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

private:
    Node* node_ {};
};

using LinkList = SingleLinkList<int>;
using LinkNode = LinkList::Node;