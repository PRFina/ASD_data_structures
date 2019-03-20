//
// Created by prf on 18/03/19.
//

#ifndef STRUTTURE_ASD_LISTGRAPH_H
#define STRUTTURE_ASD_LISTGRAPH_H

#include "../List/LinkedList.h"
#include "Graph.h"

template <class L, class W>
class ListGraph;

template <class W, class N>
struct GraphEdge{
    N _to;
    W weight;
};


template <class L, class W>
class GraphNode{
public:
    friend ListGraph<L,W>;

    typedef GraphEdge<W,int> Edge;
    typedef LinkedList<Edge> edgeList;
    typedef typename LinkedList<Edge>::position edgeListPos;
    GraphNode(): _id(-1), _free(true) {}
    GraphNode(const L& label): _label(label), _id(-1), _free(true) {}
private:


    int _id;
    bool _free;
    L _label;
    LinkedList<Edge> _edges;
};

/**
 * adj(v) = {v1,v2,...,vk} // adjacents of v
 * @tparam L node label
 * @tparam W  edge weight
 */

template <class L, class W>
class ListGraph: public Graph<L,W,GraphNode<L,W>> {
public:
    typedef Graph<L,W,GraphNode<L,W>> _Graph; //shortcut to avoid complex syntax
    typedef typename  _Graph::Label Label;
    typedef typename  _Graph::Weight Weight;
    typedef typename  _Graph::Node Node;
    typedef typename  Node::Edge Edge;

    typedef typename _Graph::NodeList NodeList;
    typedef typename _Graph::NodeListPos NodeListPos;

    ListGraph(int expected_size=50);


    void add_node(Node &n) override;

    void add_edge(const Node& from,const Node& to,const Weight& w) override;
    bool node_exists(const Node& node) const override;

    size_t nodes_count() const override;
    size_t edges_count() const override;

    bool is_empty() const override;

    Label get_label(const Node& n) const override;
    Weight get_weight(const Node& from, const Node& to) const override;

    NodeList nodes() const override;

    NodeList adjacents_nodes(const Node &n) const override;


private:
    Node* _data; //array of nodes;
    int _size;
    int _nodes_count;
    int _edges_count;

    bool isUsed(const Node& node) const;
};



template<class L, class W>
ListGraph<L, W>::ListGraph(int expected_size) {
    _size = expected_size;
    _nodes_count = 0;
    _edges_count = 0;
    _data = new Node[_size];
}


template<class L, class W>
void ListGraph<L, W>::add_node(Node& node) {
    if(_nodes_count < _size){
        int n = 0;

        while(!_data[n]._free) // search next free element
            n++;

        _data[n]._free = false; // mark as used
        _data[n]._id = n; // mark as used
        _data[n]._label = node._label;
        node._id = n; // add new id
        _nodes_count++;
    } else
        throw "Graph is full!";
}

/**
 * time complexity: O(1)
 *
 * @tparam L
 * @tparam W
 * @param from
 * @param to
 * @param w
 */
template<class L, class W>
void ListGraph<L, W>::add_edge(const Node& from,const Node& to,const Weight& w) {
    if (node_exists(from) && node_exists(to) && isUsed(from) && isUsed(to)){ //check if nodes are nodes of this graph
        Edge new_edge;
        new_edge.weight = w;
        new_edge._to = to._id;

        _data[from._id]._edges.pushBack(new_edge); // add to the adjacency list
        _edges_count++;
    } else
        throw "Invalid nodes for this graph!";

}

template<class L, class W>
bool ListGraph<L, W>::node_exists(const Node& node) const {
    return (node._id != -1);
}

template<class L, class W>
bool ListGraph<L, W>::isUsed(const Node& node) const {
    return (!_data[node._id]._free);
}

template<class L, class W>
size_t ListGraph<L, W>::nodes_count() const {
    return _nodes_count;
}

template<class L, class W>
size_t ListGraph<L, W>::edges_count() const {
    return _edges_count;
}

template<class L, class W>
bool ListGraph<L, W>::is_empty() const {
    return (_nodes_count == 0);
}

template<class L, class W>
typename ListGraph<L,W>::Label ListGraph<L, W>::get_label(const Node& node) const {
    if (node_exists(node) && isUsed(node))
        return _data[node._id]._label;
}
/**
 * time: O(adj(from))
 * @tparam L
 * @tparam W
 * @param from
 * @param to
 * @return
 */
template<class L, class W>
typename ListGraph<L,W>::Weight ListGraph<L, W>::get_weight(const Node& from, const Node& to) const {
    if (node_exists(from) && node_exists(to) && isUsed(from) && isUsed(to)){
        typename Node::edgeList& edges = _data[from._id]._edges;
        typename Node::edgeListPos pos = edges.begin();

        while (!edges.end(pos)){
            if (edges.get(pos)._to == to._id)
                return edges.get(pos).weight;
            pos = edges.next(pos);
        }

        throw "Invalid edge!"; // if function doesn't return before this line, the node to isn't in the adjacency list, so is an invalid edge
    }



}
/**
 * time: O(|V|) due to new list creation
 * @tparam L
 * @tparam W
 * @return
 */
template<class L, class W>
typename ListGraph<L,W>::NodeList ListGraph<L, W>::nodes() const {

    NodeList nodes(_size);
    NodeListPos  pos = nodes.begin();
    for(int i=0; i < _size; i++){
        if(!_data[i]._free){
            nodes.add(&_data[i],pos);
            pos = nodes.next(pos);
        }

    }

    return nodes;
}

template<class L, class W>
typename ListGraph<L,W>::NodeList ListGraph<L, W>::adjacents_nodes(const Node& node) const {

    if(node_exists(node) && isUsed(node)){

        typename Node::edgeList& edges = _data[node._id]._edges;
        typename Node::edgeListPos edgePos = edges.begin();

        NodeList nodes(edges.size());
        NodeListPos pos = nodes.begin();

        while (!edges.end(edgePos)){
            Edge edge = edges.get(edgePos);
            nodes.add(&_data[edge._to],pos);

            pos = nodes.next(pos);
            edgePos=edges.next(edgePos);
        }

        return nodes;
    } else
        throw "Invalid node";


}

#endif //STRUTTURE_ASD_LISTGRAPH_H
