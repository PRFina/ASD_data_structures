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
    LinkedTree(const LinkedTree<T>& tree);
    virtual ~LinkedTree();

    void add_root(const value_type val) override;

    void add_first_child(Node node) override;
    void add_first_child(const value_type &val, Node node);
    void add_sibling(Node node) override;
    void add_sibling(const value_type val, Node node);
    void add_subtree(Node parent, Node child, const LinkedTree<T>& subtree);


    Node get_root() const override;
    Node get_parent(const Node n) const override;
    Node get_first_child(const Node n) const override;
    Node get_next_sibling(const Node n) const override;

    bool is_empty() const override;
    bool is_leaf(const Node n) const override;
    bool is_valid(const Node n) const override;
    bool is_last_child(const Node n) const override;

    value_type get(const Node n) const override;

    void update(const value_type& val, Node n) override;
    void remove(Node n) override;
    size_t get_size() const override;


private:
    Node _root;
    int _size;
    typedef LinkedList<KTreeNode<T>*> children_list;
    typedef typename children_list::position list_pos;

    Node copy(Node from, Node parent, int& count);
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
LinkedTree<T>::LinkedTree(const LinkedTree<T> &tree) {
    int node_count = 0;
    _root = nullptr;
    _size = 0;

    if(!tree.is_empty()){
        _root = copy(tree.get_root(), nullptr, node_count);
        _size = node_count;
        _root->_parent = _root;
    }
}

template<class T>
LinkedTree<T>::~LinkedTree() {
    if(is_valid(_root))
        remove(_root);
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

template<class T>
void LinkedTree<T>::remove(Node n) {
    if(!is_leaf(n)){

        Node child = nullptr;
        bool end = false;

        while(!end){
            child = get_first_child(n);
            if(is_last_child(child)) {
                end = true;
            }
            remove(child);
        }
    }

    children_list& children = n->_parent->_children;
    list_pos pos = children.begin();
    // search leaf into parent children list and remove
    while (!children.end(pos)){
        if (children.get(pos) == n){
            children.remove(pos);
            break;
        }

        pos = children.next(pos);
    }
    delete n;
    _size--;

    if(n == _root)
        _root = nullptr;


}

template<class T>
size_t LinkedTree<T>::get_size() const {
    return _size;
}

template<class T>
void LinkedTree<T>::add_subtree(LinkedTree::Node parent, LinkedTree::Node child, const LinkedTree<T> &subtree) {
    if (!subtree.is_empty()) {
        int nodes_count = 0;
        Node subtree_root = copy(subtree.get_root(), nullptr, nodes_count);
        _size += nodes_count;

        // add as first child
        if (parent == child) {
            subtree_root->_parent = parent;
            parent->_children.pushFront(subtree_root);
        } else { // add as sibling of parent
            children_list& children = parent->_parent->_children;
            list_pos pos = children.begin();
            bool end = false;

            if (parent == _root)
                throw NoSiblingAllowed();

            while(!end){ // search parent in children list, then add as sibling
                if( parent == children.get(pos)){
                    subtree_root->_parent = parent->_parent;
                    children.add(subtree_root,pos);
                    end = true;
                }
                pos = children.next(pos);
            }
        }

    }

}
/**
 * Copy recursively the tree rooted in node from. Since each KTree node contains a parent link, in each call the
 * parent of the node will be passed as parameter to link child and parent bidirectionally. count param is incremented
 * by one unit on every node created.
 * @tparam T
 * @param from
 * @param parent
 * @param count
 * @return
 */
template<class T>
typename LinkedTree<T>::Node LinkedTree<T>::copy(Node from, Node parent, int &count) {
    Node new_node = nullptr;
    new_node = new KTreeNode<T>(from->_data, parent);
    count++;
    if(is_leaf(from))
        return new_node;

    bool end = false;
    Node child = get_first_child(from);
    while (!end){
        if (is_last_child(child))
            end = true;
        new_node->_children.pushBack(copy(child, new_node, count));
        child = get_next_sibling(child);
    }


    return new_node;
}


#endif //STRUTTURE_ASD_LINKEDTREE_H
