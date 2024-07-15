#pragma once

#include <iostream>
#include <vector>

template <typename T> class BinaryTree {
public:
    struct Node {
        T val {};
        Node* left {};
        Node* right {};

        ~Node()
        {
            delete left;
            delete right;
        }
    };

    static BinaryTree<T>::Node* create(const std::vector<T>& preorder,
                                       const std::vector<T>& inorder)
    {
        return create(preorder.begin(), preorder.end(), inorder.begin(),
                      inorder.end());
    }

    static BinaryTree<T>::Node*
    create(typename std::vector<T>::const_iterator pre_start,
           typename std::vector<T>::const_iterator pre_end,
           typename std::vector<T>::const_iterator in_start,
           typename std::vector<T>::const_iterator in_end)
    {
        if (pre_start == pre_end) {
            return nullptr;
        }

        auto root_val = pre_start;
        auto index = pre_start;
        for (auto it = in_start; it not_eq in_end; ++it) {
            if (*root_val == *it) {
                index = it;
                break;
            }
        }

        auto left_size = index - in_start;
        auto root = new BinaryTree<T>::Node { .val = *root_val };

        root->left
            = create(pre_start + 1, pre_start + left_size + 1, in_start, index);
        root->right
            = create(pre_start + left_size + 1, pre_end, index + 1, in_end);

        return root;
    }
};

using BinTree = BinaryTree<int>;
using BinTreeNode = BinTree::Node;
