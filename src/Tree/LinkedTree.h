//
// Created by prf on 13/03/19.
//

#ifndef STRUTTURE_ASD_LINKEDTREE_H
#define STRUTTURE_ASD_LINKEDTREE_H

#include "Tree.h"
#include "../List/LinkedList.h"
#include "../TreeExceptions.h"


//Forward declaration for TreeNode
template <class T>
class LinkedTree;




template <class T>
class KTreeNode{
public:
    friend LinkedTree<T>;

    KTreeNode(): _parent(nullptr) {};
    KTreeNode(const T& val, KTreeNode<T>* parent): _data(val), _parent(parent) {};

private:
    T _data;
    KTreeNode<T>* _parent;
    LinkedList<KTreeNode<T>*> _children;
};







template <class T>
class LinkedTree: public Tree<T, KTreeNode<T>*> {
public:

    typedef typename  Tree<T, KTreeNode<T>*>::value_type value_type;
    typedef typename  Tree<T, KTreeNode<T>*>::Node Node;
    LinkedTree();


    LinkedTree(const value_type& val);
    void add_root(const value_type val) override;

    void add_first_child(Node node) override;
    void add_first_child(const value_type &val, Node node);
    void add_sibling(Node node) override;
    void add_sibling(const value_type val, Node node);


    Node get_root() const override;
    Node get_parent(const Node n) const override;
    Node get_first_child(const Node n) const override;


    bool is_empty() const override;
    bool is_leaf(const Node n) const override;
    bool is_valid(const Node n) const override;
    bool is_last_child(const Node n) const override;

    value_type get(const Node n) const override;

    void update(const value_type& val, Node n) override;



    Node get_next_sibling(const Node n) const override;


private:
    Node _root;
    int _size;
    typedef LinkedList<KTreeNode<T>*> children_list;
    typedef typename children_list::position list_pos;
};

template<class T>
LinkedTree<T>::LinkedTree(): _root(nullptr), _size(0) {}

template<class T>
LinkedTree<T>::LinkedTree(const value_type &val) {
    _root = nullptr;
    _size = 0;
    add_root(val);
}


template<class T>
void LinkedTree<T>::add_root(const value_type val) {
    if(_root == nullptr){
        _root = new KTreeNode<T>(val, nullptr);
        _root->_parent = _root;
        _size = 1;
    }
    else
        throw RootExists();
}

template<class T>
void LinkedTree<T>::add_first_child(Node node) {

    if (is_valid(node)){
        Node new_node = new KTreeNode<T>;

        new_node->_parent = node;
        node->_children.pushFront(new_node);

        _size++;
    } else
        throw NullNode();

}


template<class T>
void LinkedTree<T>::add_first_child(const value_type &val, Node node) {
    if (is_valid(node)){
        Node new_node = new KTreeNode<T>(val,node);

        node->_children.pushFront(new_node);

        _size++;
    } else
        throw NullNode();

}

template<class T>
void LinkedTree<T>::add_sibling(Node n) {
    if (is_valid(n) && n != _root){
        children_list& children = n->_parent->_children;
        list_pos pos = children.begin();

        Node new_node = new KTreeNode<T>;
        new_node->_parent = n->_parent;

        while (!children.end(pos)){
            if(n == children.get(pos)){
                children.add(new_node,children.next(pos));
                _size++;
                break;
            }
            pos = children.next(pos);
        }
    } else
        throw NullNode();
}

template<class T>
void LinkedTree<T>::add_sibling(const value_type val, Node n) {
    if (is_valid(n) && n != _root){
        children_list& children = n->_parent->_children;
        list_pos pos = children.begin();

        Node new_node = new KTreeNode<T>(val, n->_parent);

        while (!children.end(pos)){
            if(n == children.get(pos)){
                children.add(new_node,children.next(pos));
                _size++;
                break;
            }
            pos = children.next(pos);
        }
    } else
        throw NullNode();
}


template<class T>
bool LinkedTree<T>::is_valid(const Node n) const {
    return (n != nullptr);
}

template<class T>
typename LinkedTree<T>::Node LinkedTree<T>::get_root() const {
    return _root;
}

template<class T>
typename LinkedTree<T>::Node LinkedTree<T>::get_parent(const Node n) const {
    if (is_valid(n))
        return n->_parent;
    else
        throw NullNode();
}

template<class T>
typename LinkedTree<T>::Node LinkedTree<T>::get_first_child(const Node n) const {
    if(!is_leaf(n))
        return n->_children.get(n->_children.begin());
}
template<class T>
bool LinkedTree<T>::is_empty() const {
    return (_root == nullptr && _size == 0);
}

template<class T>
bool LinkedTree<T>::is_leaf(const Node n) const {
    return n->_children.is_empty();
}

template<class T>
bool LinkedTree<T>::is_last_child(const Node n) const {
    if(n == _root)
        return true;
    Node last_child = n->_parent->_children.get(n->_parent->_children.last());
    return (n == last_child);
}



template<class T>
typename LinkedTree<T>::value_type LinkedTree<T>::get(const Node n) const {
    if(is_valid(n))
        return n->_data;
    else
        throw NullNode();
}

template<class T>
void LinkedTree<T>::update(const value_type& val, Node n) {
    if(is_valid(n))
        n->_data = val;
    else
        throw NullNode();
}

template<class T>
typename LinkedTree<T>::Node LinkedTree<T>::get_next_sibling(const Node n) const {

    if (is_valid(n)){
        if(!is_last_child(n)){

            children_list& siblings = n->_parent->_children;
            list_pos pos = n->_parent->_children.begin();

            //loop until the i-th child is the node n, then return the next child
            while (!siblings.end(pos)){
                if (siblings.get(pos) == n)
                    return siblings.get(siblings.next(pos));

                pos = siblings.next(pos);
            }
        } else
            return nullptr;
    } else
        throw NullNode();


}


#endif //STRUTTURE_ASD_LINKEDTREE_H
