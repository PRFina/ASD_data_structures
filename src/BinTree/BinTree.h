//
// Created by prf on 07/03/19.
//

#ifndef STRUTTURE_ASD_BINTREE_H
#define STRUTTURE_ASD_BINTREE_H

#include <iostream>

template <class T, class N>
class BinTree {

    typedef T value_type;
    typedef N Node;

    enum VisitType {PRE, POST, IN, LEVEL};

    virtual Node add_root(Node n) =0;
    virtual Node add_left_child(Node n) =0;
    virtual Node add_right_child(Node n) =0;

    virtual Node get_root() =0;
    virtual Node get_parent() =0;
    virtual Node get_left_child() =0;
    virtual Node get_right_root() =0;

    virtual value_type get(Node n) =0;
    virtual value_type update(value_type val, Node n) =0;
    virtual value_type get(Node n) =0;

    virtual bool is_empty() =0;
    virtual bool left_child_empty(Node n) =0;
    virtual bool right_child_empty(Node n) =0;

};
template <class T, class N>
void pre_visit(typename BinTree<T,N>::Node n) {
    std::cout << get(n);
    pre_visit(get_left_child(n));
    pre_visit(get_right_child(n));

}
template <class T, class N>
void in_visit(typename BinTree<T,N>::Node n) {
    pre_visit(get_left_child(n));
    std::cout << get(n);
    pre_visit(get_right_child(n));

}
template <class T, class N>
void post_visit(typename BinTree<T,N>::Node n) {
    pre_visit(get_left_child(n));
    pre_visit(get_right_child(n));
    std::cout << get(n);

}
//TODO: use queue to implement level order visit
template <class T, class N>
void level_visit(typename BinTree<T,N>::Node n) {

}

#endif //STRUTTURE_ASD_BINTREE_H
