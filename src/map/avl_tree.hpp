#if !defined(AVL_TREE)
#define AVL_TREE

#include <functional>
#include <memory>
#include <iostream>
#include "../pair/pair.hpp"
#include "../iterator/map_iterator.hpp"

namespace ft
{

    template <typename T, class Key, class Compare = std::less<Key> >
    class avl_tree
    {

    public:
        struct Node
        {
            T key;
            Node *parent;
            int height;
            Node *left;
            Node *right;
            int pos;
        };

        Node *root;

        avl_tree() { root = NULL; };
        ~avl_tree(){};

        int height(Node *N)
        {
            if (N == NULL)
                return 0;
            return N->height;
        }

        int max(int a, int b)
        {
            return (a > b) ? a : b;
        }

        Node *newNode(T key, int pos, Node *parent)
        {
            Node *node = new Node();
            node->key = key;
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->pos = pos;
            node->parent = parent;
            return (node);
        }

        Node *rightRotate(Node *y)
        {
            Node *p = y->parent;
            Node *x = y->left;
            Node *tmp = x->right;
            
            x->right = y;
            y->left = tmp;

            x->parent = p;
            y->parent = x;
            if (y->left)
                y->left->parent = y;

            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;
            return x;
        }

        Node *leftRotate(Node *x)
        {
            Node *p = x->parent;
            Node *y = x->right;
            Node *t = y->left;
  
            y->left = x;
            x->right = t;

            y->parent = p;
            x->parent = y;
            if (x->right)
                x->right->parent = x;
        
            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;

            return y;
        }

        int getBalanceFactor(Node *N)
        {
            if (N == NULL)
                return 0;
            return height(N->left) -
                   height(N->right);
        }

        template <class K>
        Node *find(K key)
        {
            Node *current = root;
            while (current != NULL)
            {
                if (key < current->key.first)
                    current = current->left;
                else if (key > current->key.first)
                    current = current->right;
                else
                    return current;
            }
            return NULL;
        }

        Node *insert(Node *node, T key, int p, Node *parent)
        {
            if (node == NULL)
                return (newNode(key, p, parent));
            if (key.first < node->key.first)
                node->left = insert(node->left, key, p, node);
            else if (key.first > node->key.first)
                node->right = insert(node->right, key, p, node);
            else
                return node;

            node->height = 1 + max(height(node->left),
                                   height(node->right));
            int balanceFactor = getBalanceFactor(node);
            if (balanceFactor > 1)
            {
                if (key.first < node->left->key.first)
                {
                    return rightRotate(node);
                }
                else if (key.first > node->left->key.first)
                {
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }
            if (balanceFactor < -1)
            {
                if (key.first > node->right->key.first) { return leftRotate(node); }
                else if (key.first < node->right->key.first) { node->right = rightRotate(node->right); return leftRotate(node); }
            }
            return node;
        }

        ft::pair<ft::TreeIterator<Node, T, Key, Compare>, bool> insertNode(T key)
        {
            Node *exist;
            if ((exist = find(key.first)) != NULL)
                return (ft::make_pair<ft::TreeIterator<Node, T, Key, Compare>, bool>(ft::TreeIterator<Node, T, Key, Compare>(exist), false));
            root = insert(root, key, -1, root);
            exist = find(key.first);
            return (ft::make_pair<ft::TreeIterator<Node, T, Key, Compare>, bool>(ft::TreeIterator<Node, T, Key, Compare>(exist), true)); // <-- something is wrong with $parent
        }

        Node *nodeWithMimumValue(Node *node)
        {
            Node *current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        Node *deleteNode(Node *root, T key)
        {

            if (root == NULL)
                return root;
            if (key.first < root->key.first)
                root->left = deleteNode(root->left, key);
            else if (key.first > root->key.first)
                root->right = deleteNode(root->right, key);
            else
            {
                if ((root->left == NULL) || (root->right == NULL))
                {
                    Node *temp = root->left ? root->left : root->right;
                    if (temp == NULL)
                    {
                        temp = root;
                        root = NULL;
                    }
                    else{
                        Node *parent = root->parent;
                        *root = *temp;
                        root->parent = parent;
                    }
                    delete temp;
                }
                else
                {
                    Node *temp = nodeWithMimumValue(root->right);
                    root->key = temp->key;
                    root->parent = temp->parent;
                    root->right = deleteNode(root->right,
                                             temp->key);
                }
            }

            if (root == NULL)
                return root;

            root->height = 1 + max(height(root->left),
                                   height(root->right));
            int balanceFactor = getBalanceFactor(root);
            if (balanceFactor > 1)
            {
                if (getBalanceFactor(root->left) >= 0)
                {
                    return rightRotate(root);
                }
                else
                {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }
            if (balanceFactor < -1)
            {
                if (getBalanceFactor(root->right) <= 0)
                {
                    return leftRotate(root);
                }
                else
                {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }
            return root;
        }

        Node *leftMostNode(Node *root) const
        {
            while (root && root->left)
                root = root->left;
            return (root);
        }

        Node *rightMostNode(Node *root) const
        {
            while (root && root->right != NULL && root->right->pos != 1)
                root = root->right;
            return (root);
        }

        void swap(avl_tree<T, Key, Compare> tree)
        {
            Node *tmp = root;
            root = tree.root;
            tree.root = tmp;
        }

        void printTree(Node *root, std::string indent, bool last)
        {
            if (root != nullptr)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                if (root->parent)
                    std::cout << "[" << root->key.first << "," << root->key.second << ", parent=" << root->parent->key.first << "]" << std::endl;
                else
                    std::cout << "[" << root->key.first << "," << root->key.second << "]" << std::endl;
                printTree(root->left, indent, false);
                printTree(root->right, indent, true);
            }
        }
    };

} // namespace ft

#endif
