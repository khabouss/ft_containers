#if !defined(RED_BLACK_TREE)
#define RED_BLACK_TREE

#include <iostream>
#include "includes/containers.hpp"

namespace ft
{

    template <class Node>
    class redBlack
    {

    public:
        typedef Node node;

        void _insertRB(node *x, node *_nil)
        {
            node *parent = x->parent;
            node *grandparent = parent->parent;
            node *uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;

            if (parent == _nil)
                x->color = BLACK_;
            else if (parent->color == BLACK_)
                return;
            else if (uncle->color == RED_)
            {
                parent->color = BLACK_;
                uncle->color = BLACK_;
                grandparent->color = RED_;
                this->_insertRB(grandparent, _nil);
            }
            else if (uncle->color == BLACK_)
            {
                if (grandparent->left->left == x || grandparent->right->right == x)
                {
                    if (grandparent->left->left == x)
                        this->_LL(grandparent, parent, _nil);
                    else if (grandparent->right->right == x)
                        this->_RR(grandparent, parent, _nil);
                    ft::swap(grandparent->color, parent->color);
                }
                else
                {
                    if (grandparent->left->right == x)
                        this->_LR(grandparent, parent, x, _nil);
                    else if (grandparent->right->left == x)
                        this->_RL(grandparent, parent, x, _nil);
                    ft::swap(grandparent->color, x->color);
                }
            }
        }

        void _deleteRB(node *v, node *u, node *_nil)
        {
            if (v->color == RED_ || u->color == RED_)
                u->color = BLACK_;
            else
                this->_doubleBlack(u, v->parent, _nil);
        }

        void _doubleBlack(node *u, node *parent, node *_nil)
        {
            node *sibling = (parent->left != u) ? parent->left : parent->right;

            if (u == _nil->right)
                return;
            else if (sibling->color == BLACK_ && (sibling->left->color == RED_ || sibling->right->color == RED_))
            {
                if (sibling == parent->left && sibling->left->color == RED_)
                    this->_LL(parent, sibling, _nil);
                else if (sibling == parent->left && sibling->right->color == RED_)
                    this->_LR(parent, sibling, sibling->right, _nil);
                else if (sibling == parent->right && sibling->right->color == RED_)
                    this->_RR(parent, sibling, _nil);
                else if (sibling == parent->right && sibling->left->color == RED_)
                    this->_RL(parent, sibling, sibling->left, _nil);

                if (sibling->left->color == RED_)
                    sibling->left->color = BLACK_;
                else
                    sibling->right->color = BLACK_;
            }
            else if (sibling->color == BLACK_)
            {
                sibling->color = RED_;
                if (parent->color == RED_)
                    parent->color = BLACK_;
                else
                    this->_doubleBlack(parent, parent->parent, _nil);
            }
            else if (sibling->color == RED_)
            {
                if (sibling == parent->left)
                    this->_LL(parent, sibling, _nil);
                else
                    this->_RR(parent, sibling, _nil);
                ft::swap(parent->color, sibling->color);
                this->_doubleBlack(u, parent, _nil);
            }
        }

        void _LL(node *grandparent, node *parent, node *_nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = parent;
            else
                grandparent->parent->left = parent;
            if (parent->right != _nil)
                parent->right->parent = grandparent;
            grandparent->left = parent->right;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->right = grandparent;
        }

        void _RR(node *grandparent, node *parent, node *_nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = parent;
            else
                grandparent->parent->left = parent;
            if (parent->left != _nil)
                parent->left->parent = grandparent;
            grandparent->right = parent->left;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->left = grandparent;
        }

        void _LR(node *grandparent, node *parent, node *x, node *_nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = x;
            else
                grandparent->parent->left = x;
            if (x->left != _nil)
                x->left->parent = parent;
            if (x->right != _nil)
                x->right->parent = grandparent;
            grandparent->left = x->right;
            parent->right = x->left;
            x->parent = grandparent->parent;
            grandparent->parent = x;
            parent->parent = x;
            x->left = parent;
            x->right = grandparent;
        }

        void _RL(node *grandparent, node *parent, node *x, node *_nil)
        {
            if (grandparent->parent->right == grandparent)
                grandparent->parent->right = x;
            else
                grandparent->parent->left = x;
            if (x->left != _nil)
                x->left->parent = grandparent;
            if (x->right != _nil)
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

#endif // RED_BLACK_TREE
