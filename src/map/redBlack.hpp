#if !defined(REDBLACK_TREE)
#define REDBLACK_TREE

#include <iostream>
#include "../utils/headers.hpp"

namespace ft
{

    template <class Node>
    class redBlack
    {

    public:
        typedef Node node;

        void insertNode(node *x, node *nil)
        {
            node *parent = x->parent;
            node *grandparent = parent->parent;
            node *uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;

            if (parent == nil)
                x->color = BLACK;
            else if (parent->color == BLACK)
                return;
            else if (uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                this->insertNode(grandparent, nil);
            }
            else if (uncle->color == BLACK)
            {
                if (grandparent->left->left == x || grandparent->right->right == x)
                {
                    if (grandparent->left->left == x)
                        this->leftLeft(grandparent, parent, nil);
                    else if (grandparent->right->right == x)
                        this->rightRight(grandparent, parent, nil);
                    ft::swap(grandparent->color, parent->color);
                }
                else
                {
                    if (grandparent->left->right == x)
                        this->leftRight(grandparent, parent, x, nil);
                    else if (grandparent->right->left == x)
                        this->rightLeft(grandparent, parent, x, nil);
                    ft::swap(grandparent->color, x->color);
                }
            }
        }

        void deleteNode(node *v, node *u, node *nil)
        {
            if (v->color == RED || u->color == RED)
                u->color = BLACK;
            else
                this->doubleBlack(u, v->parent, nil);
        }

        void doubleBlack(node *u, node *parent, node *nil)
        {
            node *sibling = (parent->left != u) ? parent->left : parent->right;

            if (u == nil->right)
                return;
            else if (sibling->color == BLACK && (sibling->left->color == RED || sibling->right->color == RED))
            {
                if (sibling == parent->left && sibling->left->color == RED)
                    this->leftLeft(parent, sibling, nil);
                else if (sibling == parent->left && sibling->right->color == RED)
                    this->leftRight(parent, sibling, sibling->right, nil);
                else if (sibling == parent->right && sibling->right->color == RED)
                    this->rightRight(parent, sibling, nil);
                else if (sibling == parent->right && sibling->left->color == RED)
                    this->rightLeft(parent, sibling, sibling->left, nil);

                if (sibling->left->color == RED)
                    sibling->left->color = BLACK;
                else
                    sibling->right->color = BLACK;
            }
            else if (sibling->color == BLACK)
            {
                sibling->color = RED;
                if (parent->color == RED)
                    parent->color = BLACK;
                else
                    this->doubleBlack(parent, parent->parent, nil);
            }
            else if (sibling->color == RED)
            {
                if (sibling == parent->left)
                    this->leftLeft(parent, sibling, nil);
                else
                    this->rightRight(parent, sibling, nil);
                ft::swap(parent->color, sibling->color);
                this->doubleBlack(u, parent, nil);
            }
        }

        void leftLeft(node *grandparent, node *parent, node *nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = parent;
            else
                grandparent->parent->left = parent;
            if (parent->right != nil)
                parent->right->parent = grandparent;
            grandparent->left = parent->right;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->right = grandparent;
        }

        void rightRight(node *grandparent, node *parent, node *nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = parent;
            else
                grandparent->parent->left = parent;
            if (parent->left != nil)
                parent->left->parent = grandparent;
            grandparent->right = parent->left;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->left = grandparent;
        }

        void leftRight(node *grandparent, node *parent, node *x, node *nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = x;
            else
                grandparent->parent->left = x;
            if (x->left != nil)
                x->left->parent = parent;
            if (x->right != nil)
                x->right->parent = grandparent;
            grandparent->left = x->right;
            parent->right = x->left;
            x->parent = grandparent->parent;
            grandparent->parent = x;
            parent->parent = x;
            x->left = parent;
            x->right = grandparent;
        }

        void rightLeft(node *grandparent, node *parent, node *x, node *nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = x;
            else
                grandparent->parent->left = x;
            if (x->left != nil)
                x->left->parent = grandparent;
            if (x->right != nil)
                x->right->parent = parent;
            grandparent->right = x->left;
            parent->left = x->right;
            x->parent = grandparent->parent;
            grandparent->parent = x;
            parent->parent = x;
            x->left = grandparent;
            x->right = parent;
        }
    };

} // namespace ft

#endif // REDBLACKTREE
