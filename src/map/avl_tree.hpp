#if !defined(AVL_TREE)
#define AVL_TREE

#include <iostream>

template <typename T>
class avl_tree
{

public:
    struct Node
    {
        T key;
        int height;
        Node *left;
        Node *right;
    };

    Node *root;

    avl_tree(){ root = NULL; };
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

    
    Node *newNode(T key)
    {
        Node *node = new Node();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return (node);
    }

    
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left),
                        height(y->right)) +
                    1;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;
        return x;
    }

    
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;
        y->height = max(height(y->left),
                        height(y->right)) +
                    1;
        return y;
    }

    
    int getBalanceFactor(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) -
               height(N->right);
    }

    
    Node *insertNode(Node *node, T key)
    {
        
        if (node == NULL)
            return (newNode(key));
        if (key.first < node->key.first)
            node->left = insertNode(node->left, key);
        else if (key.first > node->key.first)
            node->right = insertNode(node->right, key);
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
            if (key.first > node->right->key.first)
            {
                return leftRotate(node);
            }
            else if (key.first < node->right->key.first)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
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
        else if (key.first > root->key.first )
            root->right = deleteNode(root->right, key);
        else
        {
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {
                Node *temp = nodeWithMimumValue(root->right);
                root->key = temp->key;
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
            std::cout << root->key.second << std::endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }
};

#endif 
