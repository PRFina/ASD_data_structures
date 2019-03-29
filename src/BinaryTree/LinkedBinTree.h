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
    friend LinkedBinTree<T>;
    TreeNode():_parent(nullptr), _left(nullptr), _right(nullptr){};

    explicit TreeNode(const T& val): _data(val), _parent(nullptr), _left(nullptr), _right(nullptr){};
    TreeNode(const T& val, TreeNode<T>* parent, TreeNode<T>* left,TreeNode<T>* right):
            _data(val), _parent(parent), _left(left), _right(right){};

private:
    T _data;
    TreeNode<T>* _parent;
    TreeNode<T>* _left;
    TreeNode<T>* _right;

};


template <class T>
class LinkedBinTree: public BinTree<T, TreeNode<T>*> {
public:
    //TODO: assignment and equality operators
    typedef typename BinTree<T, TreeNode<T>*>::value_type value_type;
    typedef typename BinTree<T, TreeNode<T>*>::Node Node;


    LinkedBinTree(); // Construct an empty tree
    LinkedBinTree(value_type root_val); // Construct a rooted tree
    LinkedBinTree(const LinkedBinTree<T>& tree);

    void add_root(value_type val) override;
    void add_left_child(Node n) override;
    void add_left_child(value_type val, Node n) override;
    void add_right_child(Node n) override;
    void add_right_child(value_type val, Node n) override;

    void add_left_subtree(Node from, Node to);
    void add_right_subtree(Node from, Node to);

    Node get_root() const override;
    Node get_parent(Node n) const override;
    Node get_left_child(Node n) const override;
    Node get_right_child(Node n) const override;
    value_type get(Node n) const override;

    void update(value_type val, Node n) override;

    void remove(Node n) override;
    LinkedBinTree<T> extract_subtree(Node root);

    bool is_empty() const override;
    bool left_child_empty(Node n) const override;
    bool right_child_empty(Node n) const override;
    bool is_valid(Node n) const override;
    bool is_leaf(Node n) const;

    virtual ~LinkedBinTree();


private:
    size_t _size;
public:
    size_t get_size() const override;

private:
    // number of nodes
    Node _root;
    Node copy(Node from, Node parent, size_t& count);



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
LinkedBinTree<T>::LinkedBinTree(const LinkedBinTree<T> &tree) {
    _size = 0;
    _root = nullptr;

    if (!tree.is_empty()){
        size_t count = 0;
        _root = copy(tree.get_root(), nullptr, count);
        _size = count;
    }

}

template<class T>
LinkedBinTree<T>::~LinkedBinTree() {
    if(is_valid(_root))
        remove(_root);

}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::copy(LinkedBinTree::Node from, LinkedBinTree::Node parent, size_t& count) {

    if (!is_valid(from)) //base case
        return nullptr;

    Node new_node = new TreeNode<T>(from->_data);
    count++;
    new_node->_parent = parent;
    new_node->_left = copy(from->_left, new_node, count);
    new_node->_right = copy(from->_right, new_node, count);

    return new_node;

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

    if(left_child_empty(n)){
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
    if(left_child_empty(n)){
        auto child = new TreeNode<T>(val, n, nullptr, nullptr);
        n->_left = child;
        _size++;
    }
    else
        throw NodeExists();

}

template<class T>
void LinkedBinTree<T>::add_right_child(Node n) {
    if(right_child_empty(n)){
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
    if(right_child_empty(n)){
        auto child = new TreeNode<T>(val, n, nullptr, nullptr);
        n->_right = child;
        _size++;
    }
    else
        throw NodeExists();
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_root() const {
    return _root;
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_parent(Node n) const {
    if (is_valid(n))
        return n->_parent;
    else
        throw  NullNode();
}

template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_left_child(Node n) const {
    if (is_valid(n))
        return n->_left;
    else
        throw  NullNode();
}


template<class T>
typename LinkedBinTree<T>::Node LinkedBinTree<T>::get_right_child(Node n) const {
    if (is_valid(n))
        return n->_right;
    else
        throw  NullNode();
}

template<class T>
typename LinkedBinTree<T>::value_type LinkedBinTree<T>::get(Node n) const {
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
bool LinkedBinTree<T>::is_empty() const {
    return (_size == 0);
}

template<class T>
bool LinkedBinTree<T>::left_child_empty(Node n) const {
    return (n->_left == nullptr);
}

template<class T>
bool LinkedBinTree<T>::right_child_empty(Node n) const {
    return (n->_right == nullptr);
}

template<class T>
bool LinkedBinTree<T>::is_valid(Node n) const {
    return (n != nullptr);
}

template<class T>
bool LinkedBinTree<T>::is_leaf(LinkedBinTree::Node n) const {
    return(n->_left == nullptr && n->_right == nullptr);
}

template<class T>
void LinkedBinTree<T>::add_left_subtree(LinkedBinTree::Node from, LinkedBinTree::Node to) {
    if (is_valid(from) && is_valid(to)) {
        if(left_child_empty(to)) {
            size_t sub_tree_size = 0;
            to->_left = copy(from,to,sub_tree_size);
            _size += sub_tree_size;
        }
        else
            throw NodeExists();
    }
    else
        throw NullNode();

}

template<class T>
void LinkedBinTree<T>::add_right_subtree(LinkedBinTree::Node from, LinkedBinTree::Node to) {
    if (is_valid(from) && is_valid(to)) {
        if(right_child_empty(to)) {
            size_t sub_tree_size = 0;

            to->_right = copy(from,to,sub_tree_size);
            _size += sub_tree_size;
        }
        else
            throw NodeExists();
    }
    else
        throw NullNode();

}

template<class T>
LinkedBinTree<T> LinkedBinTree<T>::extract_subtree(LinkedBinTree::Node root) {

    LinkedBinTree<T> new_tree;
    size_t size = 0;
    new_tree._root = copy(root, nullptr, size);
    new_tree._size = size;

    return new_tree;
}

template<class T>
size_t LinkedBinTree<T>::get_size() const {
    return _size;
}

#endif //STRUTTURE_ASD_LINKEDBINTREE_H
