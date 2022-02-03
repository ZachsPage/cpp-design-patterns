#include <iostream>
#include <string>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//! Forward declare the BinaryTree class
template <typename T> struct BinaryTree;
////////////////////////////////////////////////////////////////////////////////
//! Class for each Node of the Binary Tree
template <typename T> struct Node
{
    Node(const T& value, Node<T>* const left, Node<T>* const right)
        : value(value), left(left), right(right)
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    explicit Node(const T& value) : value(value) { }

    ~Node() {
        if (left) delete left;
        if (right) delete right;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }

    T value = T();
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
//! Define the previously forwarded declared Binary Tree class
template <typename T> struct BinaryTree
{
    explicit BinaryTree(Node<T>* const root)
        : root{ root }
    {
        root->set_tree(this);
    }

    ~BinaryTree() { if (root) delete root; }

    // Define BinaryTree Preorder iterator
    template <typename U>
    struct PreOrderIterator
    {
        Node<U>* current;
        explicit PreOrderIterator(Node<U>* current) : current(current) { }

        Node<U>& operator*() { return *current; }
        bool operator!=(const PreOrderIterator<U>& other) { return current != other.current; }

        PreOrderIterator<U>& operator++() {
            if( current->left ) {
                current = current->left;
            } else {
                Node<T>* curr_p = current->parent;
                while( curr_p && not curr_p->right ) {
                    if( curr_p )
                        curr_p = curr_p->parent;
                }
                current = curr_p->right;
            }
            return *this;
        }
    };
    typedef PreOrderIterator<T> pre_order_it;
    pre_order_it begin() {
        Node<T>* n = root;
        return pre_order_it{ n };
    }
    pre_order_it end() {
        Node<T>* n = root;
        if (n)
            while (n->right)
                n = n->right;
        return pre_order_it{ n };
    }

private:
    Node<T>* root = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
int main()
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f

    BinaryTree<string> family{
        new Node<string>{"me", 
        new Node<string>{"mother",
            new Node<string>{"mother's mother"},
            new Node<string>{"mother's father"}
        },
        new Node<string>{"father"}
        }
    };

    cout << "Preorder Traversal:\n";
    for (decltype(family)::pre_order_it pre_it = family.begin(); pre_it != family.end(); ++pre_it)
        cout << (*pre_it).value << "\n";
}