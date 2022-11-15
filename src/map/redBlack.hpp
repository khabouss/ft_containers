#if !defined(REDBLACK_TREE)
#define REDBLACK_TREE

#include <iostream>
#include "../utils/headers.hpp"

namespace ft
{

    template <class Node, class Compare>
    class redBlack
    {

    public:
        typedef Node node;
        typedef Compare comp;

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
            // if (parent != nil->right) // <-- this case is more special than just that condition
            //     parent->color = RED;
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

        void leftRotate(node* x, node *nil)
        {
            node* y = x->right;
            x->right = y->left;
            if (y->left != nil)
            {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nil)
            {
                nil->right = y;
            }
            else if (x == x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        void rightRotate(node* x, node *nil)
        {
            node* y = x->left;
            x->left = y->right;
            if (y->right != nil)
            {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nil)
            {
                nil->right = y;
            }
            else if (x == x->parent->right)
            {
                x->parent->right = y;
            }
            else
            {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }

        // For balancing the tree after deletion
        void deleteFix(node* x, node* nil)
        {
            node* s;
            while (x != nil->right && x->color == 0)
            {
                if (x == x->parent->left)
                {
                    s = x->parent->right;
                    if (s->color == 1)
                    {
                        s->color = 0;
                        x->parent->color = 1;
                        leftRotate(x->parent, nil);
                        s = x->parent->right;
                    }

                    if (s->left->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->right->color == 0)
                        {
                            s->left->color = 0;
                            s->color = 1;
                            rightRotate(s, nil);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->right->color = 0;
                        leftRotate(x->parent, nil);
                        x = nil->right;
                    }
                }
                else
                {
                    s = x->parent->left;
                    if (s->color == 1)
                    {
                        s->color = 0;
                        x->parent->color = 1;
                        rightRotate(x->parent, nil);
                        s = x->parent->left;
                    }

                    if (s->right->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->left->color == 0)
                        {
                            s->right->color = 0;
                            s->color = 1;
                            leftRotate(s, nil);
                            s = x->parent->left;
                        }

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->left->color = 0;
                        rightRotate(x->parent, nil);
                        x = nil->right;
                    }
                }
            }
            x->color = 0;
        }

        void rbTransplant(node * u, node * v, node *nil)
        {
            if (u->parent == nil)
            {
                nil->right = v;
            }
            else if (u == u->parent->left)
            {
                u->parent->left = v;
            }
            else
            {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        node* minimum(node* n, node *nil)
        {
            while (n->left != nil)
            {
                n = n->left;
            }
            return n;
        }

        void deleteNodeHelper(node * n, node *key, node *nil, comp _comp)
        {
            node *z = nil;
            node *x;
            node *y;

            if (_comp(n->data.first, key->data.first) == false && _comp(key->data.first, n->data.first) == false)
            {
                z = n;
            }

            if (z == nil)
            {
                // Key not found in the tree
                return;
            }

            y = z;
            bool y_original_color = y->color;

            if (z->left == nil)
            {
                x = z->right;
                rbTransplant(z, z->right, nil);
            }
            else if (z->right == nil)
            {
                x = z->left;
                rbTransplant(z, z->left, nil);
            }
            else
            {
                y = minimum(z->right, nil);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z)
                {
                    x->parent = y;
                }
                else
                {
                    rbTransplant(y, y->right, nil);
                    y->right = z->right;
                    y->right->parent = y;
                }

                rbTransplant(z, y, nil);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z; // could be a prob
            if (y_original_color == 0)
            {
                deleteFix(x, nil);
            }
        }

        void deleteNode2(node* tobeDeleted, node *nil, comp _comp) {
            deleteNodeHelper(nil->right, tobeDeleted, nil, _comp);
        }

        void insertFix(node* k, node* nil)
        {
            node* u;
            while (k->parent->color == 1)
            {
                if (k->parent == k->parent->parent->right)
                {
                    u = k->parent->parent->left;
                    if (u->color == 1)
                    {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->left)
                        {
                            k = k->parent;
                            rightRotate(k, nil);
                        }
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        leftRotate(k->parent->parent, nil);
                    }
                }
                else
                {
                    u = k->parent->parent->right;

                    if (u->color == 1)
                    {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->right)
                        {
                            k = k->parent;
                            leftRotate(k, nil);
                        }
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        rightRotate(k->parent->parent, nil);
                    }
                }
                if (k == nil->right)
                {
                    break;
                }
            }
            nil->right->color = 0;
        }

        typename ft::pair<node*, bool> insert(node* n, node *nil, Compare _comp)
        {
            node* y = nil;
            node* x = nil->right;

            while (x != nil)
            {
                y = x;
                if (_comp(n->data.first, x->data.first) == false && _comp(x->data.first, n->data.first) == false)
                {
                    return ft::make_pair(x, false);
                }
                if (_comp(x->data.first, n->data.first))
                {
                    x = x->left;
                }
                else
                {
                    x = x->right;
                }
            }

            n->parent = y;
            if (y == nil)
            {
                nil->right = n;
            }
            else if (_comp(y->data.first, n->data.first))
            {
                y->left = n;
            }
            else
            {
                y->right = n;
            }

            if (n->parent == nil)
            {
                n->color = 0;
                return ft::make_pair(n, true);
            }

            if (n->parent->parent == nil)
            {
                return ft::make_pair(n, true);
            }

            insertFix(n, nil);
            return ft::make_pair(n, true);
        }
    };

} // namespace ft

#endif // REDBLACKTREE
