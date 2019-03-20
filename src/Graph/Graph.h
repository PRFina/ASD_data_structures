//
// Created by prf on 18/03/19.
//

#ifndef STRUTTURE_ASD_GRAPH_H
#define STRUTTURE_ASD_GRAPH_H

#include "../List/ArrayList.h"


template <class L, class W, class N>
class Graph {
public:
    typedef L Label;
    typedef W Weight;
    typedef N Node;

    typedef ArrayList<Node*> NodeList;
    typedef typename ArrayList<Node*>::position NodeListPos;


      virtual void add_node(Node& n) =0;
      virtual void add_edge(const Node& from, const Node& to, const Weight& w) =0;

//    virtual void remove_node(Node n) =0;


      virtual Label get_label(const Node& n) const =0;
      virtual Weight get_weight(const Node& from, const Node& to) const =0;
      virtual NodeList nodes() const =0;
      virtual NodeList adjacents_nodes(const Node& n) const =0;

//    virtual void update_label(Node n, Label l) =0;
//    virtual void update_weight(Node from, Node to, Weight w) =0;

      virtual bool is_empty() const  =0;
//    virtual bool are_adjacents(Node from, Node to) const =0;
      virtual bool node_exists(const Node& node) const =0;

      virtual size_t nodes_count() const =0;
      virtual size_t edges_count() const =0;

      virtual size_t in_degree(const Node& node) const =0;
      virtual size_t out_degree(const Node& node) const =0;



};


#endif //STRUTTURE_ASD_GRAPH_H
