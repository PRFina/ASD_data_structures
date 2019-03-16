//
// Created by prf on 13/03/19.
//

#ifndef STRUTTURE_ASD_TREE_H
#define STRUTTURE_ASD_TREE_H

#include "../Queue/Queue.h"
template <class T, class N>
class Tree {
public:
    typedef T value_type;
    typedef N Node;

    virtual void add_root(const value_type val) =0;
    virtual void add_first_child(Node node) =0;
    virtual void add_sibling(Node node) =0;


    virtual Node get_root() const =0;
    virtual Node get_parent(const Node n) const =0;
    virtual Node get_first_child(const Node n) const =0;
    virtual Node get_next_sibling(const Node n) const =0;

    virtual value_type get(const Node n) const =0;
    virtual void update(const value_type& val, Node n) =0;

//  virtual void remove(Node n) =0;

    virtual bool is_empty() const =0;
    virtual bool is_valid(const Node n) const =0;
    virtual bool is_leaf(const Node n) const =0;
    virtual bool is_last_child(const Node n) const =0;



    virtual void pre_visit(Node n);
    //virtual void in_visit(Node n);
    virtual void post_visit(Node n);
    virtual void level_visit(Node n);

    virtual int get_depth(Node n);
    virtual int get_height(Node n);




};

template<class T, class N>
void Tree<T, N>::pre_visit(Node n) {

    if(!is_valid(n))     // base case
        return;

    bool end = false;
    while (!end) {
         if(is_last_child(n))
             end = true;
         std::cout << get(n) << ", ";
         pre_visit(get_first_child(n));  // recursion
         n = get_next_sibling(n);

    }

}
/**
// TODO: review implementation (there's a segmentation bug)
template<class T, class N>
void Tree<T, N>::in_visit(Node n) {

    if(!is_valid(n))     // base case
        return;

    in_visit(get_first_child(n));
    std::cout << get(n) << ", ";

    n = get_next_sibling(n);
    bool end = false;
    while (!end) {
        if(is_last_child(n)) {
            end = true;
        }
        in_visit(get_first_child(n));  // recursion
        n = get_next_sibling(n);

    }
}
**/
template<class T, class N>
void Tree<T, N>::post_visit(Node n) {
    if(!is_valid(n))     // base case
        return;

    bool end = false;
    while (!end) {
        if(is_last_child(n))
            end = true;
        post_visit(get_first_child(n));  // recursion
        std::cout << get(n) << ", ";
        n = get_next_sibling(n);

    }
}
template<class T, class N>
void Tree<T, N>::level_visit(Node n) {

    if(!is_valid(n))
        throw NullNode();

    Queue<Node> queue;
    bool end = false;
    Node child = nullptr;
    queue.push(n);

    while(!queue.is_empty()){
        Node node = queue.front();
        queue.pop();
        std::cout << get(node) << ", ";

        if(is_leaf(node)) //if node is leaf no need to insert children, so go to next iteration.
            continue;
        // Add children of node to the queue
        child = get_first_child(node);
        while (!end){
            if(is_last_child(child))
                end = true;

            queue.push(child);
            child = get_next_sibling(child);
        }
        end = false;
    }

}

template<class T, class N>
int Tree<T, N>::get_depth(Node n) {
    if(is_valid(n)){
      int depth = 0;
      while (n != get_root()){
          n = get_parent(n);
          depth++;
      }
      return depth;
    }else
        throw NullNode();
}

template<class T, class N>
int Tree<T, N>::get_height(Node n) {
    if(is_leaf(n))
        return 0;


    int max_height = 0;
    bool end = false;
    Node child = get_first_child(n);
    while(!end){
        if(is_last_child(child))
            end = true;

        int child_height = get_height(child);
        child = get_next_sibling(child);

        max_height = std::max(max_height,child_height);

    }
    return max_height + 1;

}


#endif //STRUTTURE_ASD_TREE_H
