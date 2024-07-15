#include "algo.hpp"

#include <strings.h>

template <typename T> void traverse(typename BinaryTree<T>::Node* root)
{
    if (not root) {
        return;
    }

    traverse<int>(root->left);
    traverse<int>(root->right);
    std::cout << root->val << ", ";
}

int main()
{
    auto head = LinkList::create({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    LinkList::print(head);
    head = LinkList::reversal(head, 2, 4);
    LinkList::print(head);
    delete head;

    const std::vector<int> preorders { 3, 9, 20, 15, 7 };
    const std::vector<int> inorders { 9, 3, 15, 20, 7 };
    auto root = BinTree::create(preorders, inorders);
    traverse<int>(root);
    delete root;
}