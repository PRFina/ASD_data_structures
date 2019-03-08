//
// Created by prf on 07/03/19.
//

#ifndef STRUTTURE_ASD_BINTREE_H
#define STRUTTURE_ASD_BINTREE_H

#include <iostream>

template <class T, class N>
class BinTree {
public:
    typedef T value_type;
    typedef N Node;

    enum VisitType {PRE, POST, IN, LEVEL};

    virtual void add_root(value_type val) =0;
    virtual void add_left_child(Node n) =0;
    virtual void add_left_child(value_type val, Node n) =0;
    virtual void add_right_child(Node n) =0;
    virtual void add_right_child(value_type val, Node n) =0;

    virtual Node get_root() =0;
    virtual Node get_parent(Node n) =0;
    virtual Node get_left_child(Node n) =0;
    virtual Node get_right_child(Node n) =0;

    virtual value_type get(Node n) =0;
    virtual void update(value_type val, Node n) =0;

    virtual void remove(Node n) =0;

    virtual bool is_empty() =0;
    virtual bool left_child_empty(Node n) =0;
    virtual bool right_child_empty(Node n) =0;

    virtual void pre_visit(Node n) =0;
    virtual void in_visit(Node n) =0;
    virtual void post_visit(Node n) =0;

};

#endif //STRUTTURE_ASD_BINTREE_H
