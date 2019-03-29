//
// Created by prf on 07/03/19.
//

#ifndef STRUTTURE_ASD_BINTREE_H
#define STRUTTURE_ASD_BINTREE_H

#include <iostream>
#include "../Queue/Queue.h"
#include "../TreeExceptions.h"

/**
 * there a 2 caterogry of methods:
 * 1) Tree methods: works globally on tree
 * 2) Node methods: works locally on node
 * Since a tree can be defined recursively, sometimes this difference is not perceptible
 * and some methods that works local on node actually works on the subtree rooted at that node
 * @tparam T
 * @tparam N
 */
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

    virtual Node get_root() const =0;
    virtual Node get_parent(Node n) const =0;
    virtual Node get_left_child(Node n) const =0;
    virtual Node get_right_child(Node n) const =0;

    virtual value_type get(Node n) const =0;
    virtual void update(value_type val, Node n) =0;

    virtual void remove(Node n) =0;

    virtual bool is_empty() const =0;
    virtual bool left_child_empty(Node n) const =0;
    virtual bool right_child_empty(Node n) const =0;
    virtual bool is_valid(Node n) const =0;
    virtual bool is_leaf(Node n) const =0;
    virtual size_t get_size() const =0;

    virtual void pre_visit(Node n);
    virtual void in_visit(Node n);
    virtual void post_visit(Node n);
    virtual void level_visit(Node n);

    virtual int get_depth(Node n);
    virtual int get_height(Node n);

};

template<class T, class N>
void BinTree<T,N>::pre_visit(Node n) {

    if (is_valid(n)){
        std::cout << get(n) << ", ";
        pre_visit(get_left_child(n));
        pre_visit(get_right_child(n));
    }
}

template<class T, class N>
void BinTree<T,N>::in_visit(Node n) {
    if (is_valid(n)){
        in_visit(get_left_child(n));
        std::cout << get(n) << ", ";
        in_visit(get_right_child(n));
    }
}

template<class T, class N>
void BinTree<T,N>::post_visit(Node n) {
    if (is_valid(n)){
        post_visit(get_left_child(n));
        post_visit(get_right_child(n));
        std::cout << get(n) << ", ";
    }
}

template<class T, class N>
int BinTree<T, N>::get_depth(Node n) {
    if (is_valid(n)){
        int depth = 0;
        while( n != get_root()){
            depth++;
            n = get_parent(n);
        }

        return depth;
    } else
        throw NullNode();


}

template<class T, class N>
int BinTree<T, N>::get_height(Node n) {
    if(is_valid(n)) {
        return (std::max(get_height(get_left_child(n)), get_height(get_right_child(n))) + 1);
    }
    else
        return -1; // recursion base case
}

template<class T, class N>
void BinTree<T, N>::level_visit(Node n) {
    Queue<N> queue;
    queue.push(n);
    N node;
    while (!queue.is_empty()){
        node = queue.front();
        std::cout << get(node) << ", ";
        queue.pop();

        if(!left_child_empty(node))
            queue.push(get_left_child(node));
        if(!right_child_empty(node))
            queue.push(get_right_child(node));
    }

}

#endif //STRUTTURE_ASD_BINTREE_H
