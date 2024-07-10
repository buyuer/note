#pragma once

#include <iostream>
#include <vector>

template <typename T = int> struct SingleLinkNode {
    T val;
    SingleLinkNode<T>* next {};

    ~SingleLinkNode<T>() { delete next; }

    void print()
    {
        auto p = this;
        std::cout << "[";
        while (p) {
            std::cout << p->val << ", ";
            p = p->next;
        }
        std::cout << "]" << std::endl;
    }

    static void release(SingleLinkNode<T>* head)
    {
        auto p = head;
        while (p) {
            auto next = p->next;
            delete p;
            p = next;
        }
    }

    static SingleLinkNode<T>* create(const std::vector<T>& items)
    {
        SingleLinkNode* head { nullptr };
        SingleLinkNode** p { &head };
        for (const auto& item : items) {
            *p = new SingleLinkNode { .val = item };
            p = &((*p)->next);
        }
        return head;
    }
};

template <typename T = int> struct BinaryTree {
    T val;
    BinaryTree<T>* left;
    BinaryTree<T>* right;
};

using Node = SingleLinkNode<int>;