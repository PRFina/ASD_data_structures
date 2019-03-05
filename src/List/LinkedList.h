//
// Created by prf on 04/03/19.
//

#ifndef STRUTTURE_ASD_LINKEDLIST_H
#define STRUTTURE_ASD_LINKEDLIST_H

#include "List.h"
#include <iostream>

template <class T> class LinkedList;
/*******************************************************************
NODE
*******************************************************************/
template <class T>
class Node
{
public:
    friend class LinkedList<T>;
    Node(): _prev(nullptr), _next(nullptr) {};
    Node(T value): _data(value), _prev(nullptr), _next(nullptr) {};
    Node(T value, Node<T>* prev, Node<T>* next): _data(value), _prev(prev), _next(next) {};



private:
    T _data;
    Node<T>* _prev;
    Node<T>* _next;
};


/*******************************************************************
LINKED LIST
*******************************************************************/
// TODO: assignment and equality operators;
template<class T>
class LinkedList: public List<T, Node<T>*> {
public:
    typedef typename List<T, Node<T>*>::value_type value_type;
    typedef typename List<T, Node<T>*>::position position;

    LinkedList();
    LinkedList(const T& val, const unsigned int length);
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

    void create() override;
    bool is_empty() const override;

    unsigned int size() const override;

    value_type get(position position) const override;
    void add(const value_type &v, position pos) override;
    void pushBack(const value_type& v);
    void pushFront(const value_type& v);

    void update(const value_type &v, position pos) override;
    void remove(position pos) override;
    void popBack();
    void popFront();

    void clear();
    position begin() const override;
    position last() const;
    bool end(position pos) const override;
    position previous(position pos) const override;

    position next(position pos) const override;

private:
    Node<T>* _head; //_head->_prev is the last element, _head->_next it he first element
    unsigned int _length;

};

template <class T>
LinkedList<T>::LinkedList() {

    _head = new Node<T>;
    _head->_prev = _head;
    _head->_next =_head;
    _length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const T &val, const unsigned int length) {
    _head = new Node<T>;
    _head->_prev = _head;
    _head->_next =_head;
    _length = 0;

    for(int i=0; i < length; i++)
        pushBack(val);
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    _head = new Node<T>;
    _head->_prev = _head;
    _head->_next =_head;
    _length =0;

    position pos = list.begin();
    while (!list.end(pos)){
        pushBack(list.get(pos));
        pos = list.next(pos);
    }
}

template<class T>
void LinkedList<T>::create() {

}

template<class T>
bool LinkedList<T>::is_empty() const {
    return (_length == 0) && _head == _head->_next;
}

template<class T>
unsigned int LinkedList<T>::size() const {
    return _length;
}

template<class T>
typename LinkedList<T>::value_type LinkedList<T>::get(position pos) const {
    if(!end(pos))
        return pos->_data;
}

template<class T>
void LinkedList<T>::add(const value_type &v, position pos) { // add before pos
    position newNode = new Node<T>(v, pos->_prev, pos);

    pos->_prev->_next = newNode;
    pos->_prev = newNode;

    _length++;

}

template<class T>
void LinkedList<T>::pushBack(const value_type &v) {
    add(v,_head); //add before head since head->prev is the last one
}

template<class T>
void LinkedList<T>::pushFront(const value_type &v) {
    add(v,begin());
}


template<class T>
void LinkedList<T>::update(const value_type &v, position pos) {
    if(!end(pos))
        pos->_data = v;
}

template<class T>
void LinkedList<T>::remove(position pos) {
    if( !is_empty() && !end(pos)){
        pos->_prev->_next = pos->_next;
        pos->_next->_prev = pos->_prev;

        delete pos;
        _length--;
    }
}

template<class T>
void LinkedList<T>::popBack() {
    remove(last());

}

template<class T>
void LinkedList<T>::popFront() {
    remove(begin());

}

template<class T>
typename LinkedList<T>::position LinkedList<T>::begin() const {
    return _head->_next;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::last() const {
    return _head->_prev;
}

template<class T>
bool LinkedList<T>::end(position pos) const {
    return (pos == _head);
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::previous(position  pos) const {
    return pos->_prev;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::next(position pos) const {
    return pos->_next;
}

template<class T>
void LinkedList<T>::clear() {
    while(!is_empty())
        remove(begin());
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
    delete _head;

}


#endif //STRUTTURE_ASD_LINKEDLIST_H
