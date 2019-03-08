//
// Created by prf on 07/03/19.
//

#ifndef STRUTTURE_ASD_ARRAYBINTREE_H
#define STRUTTURE_ASD_ARRAYBINTREE_H

#include "BinTree.h"




template <class T>
class ArrayBinTree: public BinTree<T, int> {
public:
    static const int NIL = -1;
    typedef typename BinTree<T, int>::value_type value_type;
    typedef typename BinTree<T, int>::Node Node;
    //TODO: make constructor copy, assignement and equality operators
    ArrayBinTree();
    ArrayBinTree(size_t size);
    ~ArrayBinTree();
    void print();

    void add_root(value_type val) override;
    void add_left_child(Node n) override;
    void add_left_child(value_type val, Node n);
    void add_right_child(Node n) override;
    void add_right_child(value_type val, Node n);

    bool is_empty() override;
    bool left_child_empty(Node n) override;

    bool right_child_empty(Node n) override;
    Node get_root() override;
    Node get_parent(Node n) override;
    Node get_left_child(Node n) override;
    Node get_right_child(Node n) override;

    value_type get(Node n) override;

    void update(value_type val, Node n) override;
    void remove(Node n) override;



private:
    struct _Cell {
        Node parent;
        Node left;
        Node right;
        value_type value;
    };

    _Cell* _data;
    size_t _size;
    size_t _MAX_SIZE;
    Node _root;
    Node _free_pos;

    bool isFull();



};

template<class T>
ArrayBinTree<T>::ArrayBinTree() {
    _MAX_SIZE = 100;
    _data = new _Cell[_MAX_SIZE];
    _size = 0;
    _root = NIL;
    _free_pos = 0;

    for (int i = 0; i < _MAX_SIZE ; i++) {
        _data[i].left = (i+1) % _MAX_SIZE;
    }

}

template<class T>
typename ArrayBinTree<T>::value_type ArrayBinTree<T>::get(Node n) {
    if (n != NIL)
        return _data[n].value;
}

template<class T>
void ArrayBinTree<T>::add_left_child(Node n) {

    if(is_empty())
        throw std::domain_error("Empty Tree");
    if (isFull())
        throw std::domain_error("Tree is full");
    if (n == NIL)
        throw std::domain_error("Null Node");
    if (_data[n].left != NIL)
        throw std::domain_error("Node already exists");
    else{
        Node new_node = _free_pos;
        _free_pos = _data[_free_pos].left;

        _data[n].left = new_node;
        _data[new_node].parent = n;

        _data[new_node].left = NIL;
        _data[new_node].right = NIL;

        _size++;

    }
}

template<class T>
void ArrayBinTree<T>::add_left_child(value_type val, Node n) {
    if(is_empty())
        throw std::domain_error("Empty Tree");
    if (isFull())
        throw std::domain_error("Tree is full");
    if (n == NIL)
        throw std::domain_error("Null Node");
    if (_data[n].left != NIL)
        throw std::domain_error("Node already exists");
    else{
        Node new_node = _free_pos;
        _free_pos = _data[_free_pos].left;

        _data[n].left = new_node;
        _data[new_node].parent = n;
        _data[new_node].value = val;
        _data[new_node].left = NIL;
        _data[new_node].right = NIL;

        _size++;

    }
}

template<class T>
void ArrayBinTree<T>::add_right_child(Node n) {
    if(is_empty())
        throw std::domain_error("Empty Tree");
    if (isFull())
        throw std::domain_error("Tree is full");
    if (n == NIL)
        throw std::domain_error("Null Node");
    if (_data[n].right != NIL)
        throw std::domain_error("Node already exists");
    else{
        Node new_node = _free_pos;
        _free_pos = _data[_free_pos].left;

        _data[n].right = new_node;
        _data[new_node].parent = n;

        _data[new_node].left = NIL;
        _data[new_node].right = NIL;

        _size++;
    }

}

template<class T>
void ArrayBinTree<T>::add_right_child(value_type val, ArrayBinTree::Node n) {
    if(is_empty())
        throw std::domain_error("Empty Tree");
    if (isFull())
        throw std::domain_error("Tree is full");
    if (n == NIL)
        throw std::domain_error("Null Node");
    if (_data[n].right != NIL)
        throw std::domain_error("Node already exists");
    else{
        Node new_node = _free_pos;
        _free_pos = _data[_free_pos].left;

        _data[n].right = new_node;
        _data[new_node].parent = n;
        _data[new_node].value = val;
        _data[new_node].left = NIL;
        _data[new_node].right = NIL;

        _size++;
    }
}

template<class T>
void ArrayBinTree<T>::update(value_type val, Node n) {
    if (n != NIL)
        _data[n].value = val;
}

template<class T>
bool ArrayBinTree<T>::is_empty() {
    return (_size == 0);
}

template<class T>
bool ArrayBinTree<T>::left_child_empty(Node n) {
    return (_data[n].left == NIL);
}

template<class T>
typename ArrayBinTree<T>::Node ArrayBinTree<T>::get_root() {
    return _root;
}

template<class T>
typename ArrayBinTree<T>::Node ArrayBinTree<T>::get_parent(Node n) {
    if ( n != _root)
        return _data[n].parent;
    else
        return n;
}

template<class T>
typename ArrayBinTree<T>::Node ArrayBinTree<T>::get_left_child(Node n) {
    if ( !left_child_empty(n))
        return _data[n].left;
    else
        return NIL;
}

template<class T>
typename ArrayBinTree<T>::Node ArrayBinTree<T>::get_right_child(Node n) {
    if ( !right_child_empty(n))
        return _data[n].right;
    else
        return NIL;
}

template<class T>
bool ArrayBinTree<T>::right_child_empty(ArrayBinTree<T>::Node n) {
    return (_data[n].right == NIL);
}

template<class T>
void ArrayBinTree<T>::add_root(value_type val) {
    if (is_empty() && _root == NIL){
        _root = _free_pos;
        _free_pos = _data[_free_pos].left; // new child will be inserted always as left child first

        _data[_root].value = val;
        _data[_root].left = NIL;
        _data[_root].right = NIL;

        _size++;
    }

}

template<class T>
void ArrayBinTree<T>::print() {
    for (int i = 0; i < _size ; ++i) {
        std::cout << "array pos: " << i << "   (" << _data[i].value << ", " << _data[i].parent << ", "
                  << _data[i].left << ", " << _data[i].right << ")" << std::endl;
    }

}

template<class T>
bool ArrayBinTree<T>::isFull() {
    return(_size == _MAX_SIZE);
}

template<class T>
void ArrayBinTree<T>::remove(Node n) {

    if (n != NIL){

        if (!left_child_empty(n))
            remove(_data[n].left); // remove left subtree rooted ad n

        if (!right_child_empty(n))
        remove(_data[n].right); // remove right subtree rooted ad n

        if ( n != _root) {
            Node parent = get_parent(n);
            if (_data[parent].left == n) // check if the node is a left child of the parent
                _data[parent].left = NIL; // "delete the node setting it to NIL"
            else
                _data[parent].right = NIL;
        }
        else
            _root = NIL; // delete the root

        _size--;
        _data[n].left = _free_pos;
        _free_pos = n; // set the next free position to the deleted node
        n = NIL;
    }
    else
        throw std::domain_error("Null node");
}

template<class T>
ArrayBinTree<T>::~ArrayBinTree() {
    remove(_root); //remove
    delete[] _data;
}

#endif //STRUTTURE_ASD_ARRAYBINTREE_H


