//
// Created by prf on 18/03/19.
//

#ifndef STRUTTURE_ASD_GRAPH_H
#define STRUTTURE_ASD_GRAPH_H

#include "../List/ArrayList.h"

template <class N, class W>
class Edge{
public:
    N from;
    N to;
    W weight;

};


template <class L, class W, class N>
class Graph {
public:
    typedef L Label;
    typedef W Weight;
    typedef N Node;
    typedef Edge<Node,Weight> Edge;

    typedef ArrayList<Node*> NodeList;
    typedef typename ArrayList<Node*>::position NodeListPos;

    typedef ArrayList<Edge> EdgeList;

    virtual void add_node(Node n) =0;
    virtual void add_edge(Node from, Node to, Weight w) =0;

    virtual void remove_node(Node n) =0;
    virtual void add_edge(Node from, Node to) =0;

    virtual Label get_label(Node n) const =0;
    virtual Label get_weight(Node from, Node to) const =0;
    virtual NodeList nodes() const =0;
    virtual NodeList adjacents_nodes(Node n) const =0;

    virtual void update_label(Node n, Label l) =0;
    virtual void update_weight(Node from, Node to, Weight w) =0;

    virtual bool is_empty() const  =0;
    virtual bool are_adjacents(Node from, Node to) const =0;

    virtual size_t nodes_count() const =0;
    virtual size_t edges_count() const =0;


};


#endif //STRUTTURE_ASD_GRAPH_H
