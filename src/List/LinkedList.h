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

template<class T>
class LinkedList: public List<T, Node<T>*> {
public:
    typedef typename List<T, Node<T>*>::value_type value_type;
    typedef typename List<T, Node<T>*>::position position;

    LinkedList();
    LinkedList(const unsigned int size, const int step);
    LinkedList(const LinkedList<T>& list);

    void create() override;

    bool is_empty() const override;
    unsigned int size() const override;

    value_type get(position position) const override;
    void add(const value_type &v, position pos) override;
    void update(const value_type &v, position pos) override;
    void remove(position pos) override;

    void pushBack(const value_type& v);
    void pushFront(const value_type& v);

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

template <class T>
LinkedList<T>::LinkedList(const unsigned int size, const int step) {

}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {

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


#endif //STRUTTURE_ASD_LINKEDLIST_H
