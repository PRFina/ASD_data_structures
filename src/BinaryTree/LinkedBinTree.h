//
// Created by prf on 09/03/19.
//

#ifndef STRUTTURE_ASD_LINKEDBINTREE_H
#define STRUTTURE_ASD_LINKEDBINTREE_H


#include "BinTree.h"
#include "../TreeExceptions.h"

template <class T>
class LinkedBinTree;

template <class T>
class TreeNode{

    TreeNode():_parent(nullptr), _left(nullptr), _right(nullptr){};
    TreeNode(const T& val): _data(val), _parent(nullptr), _left(nullptr), _right(nullptr){};
    TreeNode(const T& val, TreeNode<T>* parent, TreeNode<T>* left,TreeNode<T>* right):
            _data(val), _parent(parent), _left(left), _right(right){};
    friend LinkedBinTree<T>;
private:
    T _data;
    TreeNode<T>* _parent;
    TreeNode<T>* _left;
    TreeNode<T>* _right;

};


template <class T>
class LinkedBinTree: public BinTree<T, TreeNode<T>*> {
public:
    //TODO: add copy constructor, assignment and equality operators
    typedef typename BinTree<T, TreeNode<T>*>::value_type value_type;
    typedef typename BinTree<T, TreeNode<T>*>::Node Node;


    LinkedBinTree(); // Construct an empty tree
    LinkedBinTree(value_type root_val); // Construct a rooted tree

    void add_root(value_type val) override;
    void add_left_child(Node n) override;
    void add_left_child(value_type val, Node n) override;
    void add_right_child(Node n) override;
    void add_right_child(value_type val, Node n) override;

    Node get_root() override;
    Node get_parent(Node n) override;
    Node get_left_child(Node n) override;
    Node get_right_child(Node n) override;
    value_type get(Node n) override;

    void update(value_type val, Node n) override;
    void remove(Node n) override;

    bool is_empty() override;
    bool left_child_empty(Node n) override;
    bool right_child_empty(Node n) override;
    bool is_valid(Node n) override;
    bool is_leaf(Node n);

private:
    int _size; // number of nodes
    Node _root;



};

template<class T>
LinkedBinTree<T>::LinkedBinTree():_size(0), _root(nullptr) {}

template<class T>
LinkedBinTree<T>::LinkedBinTree(value_type root_val) {
    _root = new TreeNode<T>(root_val);
    _root->_parent = _root;
    _size = 1;
}

template<class T>
void LinkedBinTree<T>::add_root(value_type val) {
    if (_root == nullptr){
        _root = new TreeNode<T>(val);
        _root->_parent = _root;
        _size = 1;
    }
    else
        throw RootExists();

}

template<class T>
void LinkedBinTree<T>::add_left_child(Node n) {

    if(n->_left == nullptr){
        auto child = new TreeNode<T>;
        n->_left = child;
        child->_parent = n;
        _size++;
    }
    else
        throw NodeExists();

}

template<class T>
void LinkedBinTree<T>::add_left_child(value_type val, Node n) {
    if(n->_left == nullptr){
        auto child = new TreeNode<T>(val, n, nullptr, nullptr);
        n->_left = child;
        _size++;
    }
    else
        throw NodeExists();

}

template<class T>
void LinkedBinTree<T>::add_right_child(Node n) {
    if(n->_right == nullptr){
        auto child = new TreeNode<T>();
        n->_right = child;
        child->_parent = n;
        _size++;
    }
    else
        throw NodeExists();
}

template<class T>
void LinkedBinTree<T>::add_right_child(value_type val, Node n) {
    if(n->_right == nullptr){
        auto child = new TreeNode<T>(val, n, nullptr, nullptr);
        n->_right = child;
        _size++;
    }
    else
        throw NodeExists();
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_root() {
    return _root;
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_parent(Node n) {
    if (is_valid(n))
        return n->_parent;
    else
        throw  NullNode();
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_left_child(Node n) {
    if (is_valid(n))
        return n->_left;
    else
        throw  NullNode();
}


template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_right_child(Node n) {
    if (is_valid(n))
        return n->_right;
    else
        throw  NullNode();
}

template<class T>
typename LinkedBinTree<T>::value_type LinkedBinTree<T>::get(Node n) {
    if (is_valid(n))
        return n->_data;
    else
        throw  NullNode();
}

template<class T>
void LinkedBinTree<T>::update(value_type val, Node n) {
    if (is_valid(n))
        n->_data = val;
    else
        throw  NullNode();
}

template<class T>
void LinkedBinTree<T>::remove(Node n) {
    if (is_valid(n)) {
        //Check if there is a left /right rooted subtree in n
        if(!left_child_empty(n))
            remove(n->_left);
        if(!right_child_empty(n))
            remove(n->_right);

        //Unlink parent
       if(n->_parent->_left == n)
           n->_parent->_left = nullptr;
       if(n->_parent->_right == n)
           n->_parent->_right = nullptr;

       delete n;
       _size--;

       if (n == _root) // special case for root
          _root = nullptr;
    }
}

template<class T>
bool LinkedBinTree<T>::is_empty() {
    return (_size == 0);
}

template<class T>
bool LinkedBinTree<T>::left_child_empty(Node n) {
    return (n->_left == nullptr);
}

template<class T>
bool LinkedBinTree<T>::right_child_empty(Node n) {
    return (n->_right == nullptr);
}

template<class T>
bool LinkedBinTree<T>::is_valid(Node n) {
    return (n != nullptr);
}

template<class T>
bool LinkedBinTree<T>::is_leaf(LinkedBinTree::Node n) {
    return(n->_left == nullptr && n->_right == nullptr);
}


#endif //STRUTTURE_ASD_LINKEDBINTREE_H
