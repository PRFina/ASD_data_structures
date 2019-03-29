//
// Created by prf on 18/03/19.
//

#ifndef STRUTTURE_ASD_LISTGRAPH_H
#define STRUTTURE_ASD_LISTGRAPH_H

#include "../List/LinkedList.h"
#include "Graph.h"
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

template <class L, class W>
class ListGraph;

template <class W, class N>
struct GraphEdge{
    N _to;
    W _weight;
};

// TODO: replace throw string with trow exceptions

template <class L, class W>
class GraphNode{
public:
    friend ListGraph<L,W>;
    static const int NIL = -1;

    typedef GraphEdge<W,int> Edge;
    typedef LinkedList<Edge> edgeList;
    typedef typename LinkedList<Edge>::position edgeListPos;
    GraphNode(): _id(NIL), _free(true), _visited(false) {}
    GraphNode(const L& label): _label(label), _id(NIL), _free(true), _visited(false) {}

private:
    int _id;
    bool _free;
    L _label;
    LinkedList<Edge> _edges;
    bool _visited;
};

/**
 * This implementation models a Directed Weighted Graph. For non oriented graph some methods
 * (add_edge, degree, remove_edge) should be modified accordingly to the semantics or non orientedness
 * adj(v) = {v1,v2,...,vk} // adjacents of v
 * @tparam L node label
 * @tparam W  edge weight
 */

template <class L, class W>
class ListGraph: public Graph<L,W,GraphNode<L,W>> {
public:
    typedef Graph<L,W,GraphNode<L,W>> _Graph; // shortcut to avoid complex syntax
    typedef typename  _Graph::Label Label;
    typedef typename  _Graph::Weight Weight;
    typedef typename  _Graph::Node Node;
    typedef typename  Node::Edge Edge;

    typedef typename _Graph::NodeList NodeList;
    typedef typename _Graph::NodeListPos NodeListPos;

    ListGraph(size_t expected_size=50);


    void add_node(Node &n) override;

    void add_edge(const Node& from,const Node& to,const Weight& w) override;
    bool node_exists(const Node& node) const override;

    void update_label(Node n, const Label& l) override;
    void update_weight(Node& from, Node& to, const Weight& w) override;

    size_t nodes_count() const override;
    size_t edges_count() const override;

    bool is_empty() const override;

    Label get_label(const Node& n) const override;
    Weight get_weight(const Node& from, const Node& to) const override;

    NodeList nodes() const override;
    NodeList adjacents_nodes(const Node &n) const override;

    size_t in_degree(const Node &node) const override;
    size_t out_degree(const Node &node) const override;

    void remove_node(Node& n) override;
    void remove_edge(const Node &from, const Node &to) override;

    void DFS_visit(const Node &start_node) const override;

    void BFS_visit(const Node &start_node) const override;

    virtual ~ListGraph();


private:
    Node* _data; //array of nodes;
    size_t _size;
    size_t _nodes_count;
    size_t _edges_count;

    bool isUsed(const Node& node) const;
};



template<class L, class W>
ListGraph<L, W>::ListGraph(size_t expected_size) {
    _size = expected_size;
    _nodes_count = 0;
    _edges_count = 0;
    _data = new Node[_size];
}

/**
 * Node must be unique
 * time: worst case O(|V|) because search linearly in the nodes array
 * @tparam L
 * @tparam W
 * @param node
 */
template<class L, class W>
void ListGraph<L, W>::add_node(Node& node) {
    if(_nodes_count < _size){
        if( node._id == Node::NIL) {

            int n = 0;
            while(isUsed(_data[n])) // search next free element
                n++;

            _data[n]._free = false; // mark as used
            _data[n]._id = n; // mark as used
            _data[n]._label = node._label;

            node._id = n; // add new id
            _nodes_count++;
        } else
            throw "Node isn't a new node";
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
        new_edge._weight = w;
        new_edge._to = to._id;

        _data[from._id]._edges.pushBack(new_edge); // add to the adjacency list
        _edges_count++;
    } else
        throw "Invalid nodes for this graph!";

}

template<class L, class W>
bool ListGraph<L, W>::node_exists(const Node& node) const {
    return (node._id != Node::NIL);
}

template<class L, class W>
bool ListGraph<L, W>::isUsed(const Node& node) const {
    if (node_exists(node))
        return (!_data[node._id]._free);
    return false;
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
                return edges.get(pos)._weight;
            pos = edges.next(pos);
        }

        throw "Invalid edge!"; // if function doesn't return before this line, the node to isn't in the adjacency list, so is an invalid edge
    }



}


template<class L, class W>
void ListGraph<L, W>::update_label(Node node, const Label& label) {
    if (node_exists(node) && isUsed(node))
        _data[node._id]._label = label;
}

/**
 * time: O(adj(from))
 * @tparam L
 * @tparam W
 * @param from
 * @param to
 * @param w
 */

template<class L, class W>
void ListGraph<L, W>::update_weight(Node& from, Node& to, const Weight& w) {
    if (node_exists(from) && isUsed(from) && node_exists(to) && isUsed(to)){
        typename Node::edgeList& edges = _data[from._id]._edges;
        typename Node::edgeListPos pos = edges.begin();

        while(!edges.end(pos)){
            if(edges.get(pos)._to == to._id){

                Edge e = edges.get(pos);
                e._weight = w;
                edges.update(e, pos);
                return;
            }
        }

        throw "invalid edge!";
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
/**
 * time: O(|V|*sum(0,|V|,adj(v_i))) = O(|V||E|)
 * @tparam L
 * @tparam W
 * @param node
 * @return
 */
template<class L, class W>
size_t ListGraph<L, W>::in_degree(const Node& node) const {
    size_t  in_degree = 0;
    if(node_exists(node) && isUsed(node)){

        for(int i=0; i < _size; i++){ //loop trough all nodes
            if(isUsed(_data[i])) {
                NodeList adj_list = adjacents_nodes(_data[i]);
                NodeListPos pos = adj_list.begin();

                while (!adj_list.end(pos)){ // loop trough adjacents nodes
                    if(adj_list.get(pos)->_id == node._id)
                        in_degree++;
                    pos = adj_list.next(pos);
                }
            }
        }
    }

    return in_degree;
}

/**
 * time: O(1) due to size operator in edge list, O(adj(node)) otherwise
 * @tparam L
 * @tparam W
 * @param node
 * @return
 */
template<class L, class W>
size_t ListGraph<L, W>::out_degree(const Node& node) const {
    if(node_exists(node) && isUsed(node))
        return _data[node._id]._edges.size();
    else
        throw "Invalid node";
}

template<class L, class W>
void ListGraph<L, W>::remove_node(Node& node) {
    if (node_exists(node) && isUsed(node)){
        if(node._edges.is_empty()){
            _data[node._id]._free = true; //mark as deleted
            _data[node._id]._id = Node::NIL; //invalidate the node
            _data[node._id]._edges.clear(); //remove all elements from adjacency list

            node._id = Node::NIL; // set node with invalid id
        } else {
            //TODO: loop trough al nodes adjacency list and find n and then delete the edge
            throw "Not an isolated node";
        }

    }

}

template<class L, class W>
void ListGraph<L, W>::remove_edge(const Node& from, const Node& to) {
    if (node_exists(from) && isUsed(from) && node_exists(to) && isUsed(to)){
        typename Node::edgeList& edges = _data[from._id]._edges;
        typename Node::edgeListPos pos = edges.begin();

        bool found = false;
        while(!edges.end(pos) && !found){
            if(edges.get(pos)._to == to._id){
                found = true;
                edges.remove(pos);
            }
            pos = edges.next(pos);
        }
    }

}

template<class L, class W>
void ListGraph<L, W>::DFS_visit(const Node& start_node) const {
    Stack<Node> stack;
    _data[start_node._id]._visited = true;
    stack.push(_data[start_node._id]);

    while (!stack.is_empty()) {
        Node current = stack.top();
        std::cout << current._label << ", ";
        stack.pop();

        NodeList neighbors = adjacents_nodes(current);
        NodeListPos pos = neighbors.begin();

        while (!neighbors.end(pos)) {
            if (!neighbors.get(pos)->_visited) {
                neighbors.get(pos)->_visited = true;
                stack.push(*neighbors.get(pos));
            }
            pos = neighbors.next(pos);
        }

    }

    NodeList nodes = this->nodes();
    NodeListPos pos = nodes.begin();

    while (!nodes.end(pos)) {
        nodes.get(pos)->_visited = false;
        pos = nodes.next(pos);
    }
}

template<class L, class W>
void ListGraph<L, W>::BFS_visit(const Node& start_node) const {
    Queue<Node> queue;
    _data[start_node._id]._visited = true;
    queue.push(_data[start_node._id]);

    while (!queue.is_empty()) {
        Node current = queue.front();
        std::cout << current._label << ", ";
        queue.pop();

        NodeList neighbors = adjacents_nodes(current);
        NodeListPos pos = neighbors.begin();

        while (!neighbors.end(pos)) {
            if (!neighbors.get(pos)->_visited) {
                neighbors.get(pos)->_visited = true;
                queue.push(*neighbors.get(pos));
            }
            pos = neighbors.next(pos);
        }

    }

    NodeList nodes = this->nodes();
    NodeListPos pos = nodes.begin();

    while (!nodes.end(pos)) {
        nodes.get(pos)->_visited = false;
        pos = nodes.next(pos);
    }
}

template<class L, class W>
ListGraph<L, W>::~ListGraph() {
    delete[] _data;
    _size = 0;
    _nodes_count = 0;
    _edges_count = 0;
}


#endif //STRUTTURE_ASD_LISTGRAPH_H
