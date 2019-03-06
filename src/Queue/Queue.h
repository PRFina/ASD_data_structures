//
// Created by prf on 06/03/19.
//

#ifndef STRUTTURE_ASD_CLASS_H
#define STRUTTURE_ASD_CLASS_H

#include "../List/LinkedList.h"

//Forward declaration for operator<< "non template" compilation error
template <class T>
class Queue;

template <class T>
std::ostream &operator<< (std::ostream &os, const Queue<T> &queue);


template <class T>
class Queue {
    typedef typename LinkedList<T>::value_type value_type;

public:
    Queue();
    Queue(const Queue<T>& Queue);

    void push(const value_type& value);
    void pop();

    value_type front();
    value_type back();

    std::size_t size();
    bool is_empty();

    friend std::ostream &operator<< <T>(std::ostream &os, const Queue<T> &queue);

private:
    LinkedList<T> _list;
};

template<class T>
Queue<T>::Queue():_list(_list) {}

template<class T>
Queue<T>::Queue(const Queue <T> &Queue): _list(Queue._list) {}

template<class T>
void Queue<T>::push(const value_type &value) {
    _list.pushFront(value);
}

template<class T>
void Queue<T>::pop() {
    _list.popBack();
}

template<class T>
typename Queue<T>::value_type Queue<T>::front() {
    return _list.get(_list.last());
}

template<class T>
typename Queue<T>::value_type Queue<T>::back() {
    return _list.get(_list.begin());
}

template<class T>
std::size_t Queue<T>::size() {
    return _list.size();
}

template<class T>
bool Queue<T>::is_empty() {
    return _list.is_empty();
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &queue) {

    if (!queue._list.is_empty()){
        os << " -> " << queue._list<< " ->";
    }
    else
        os << "[]";


    return os;
}

#endif //STRUTTURE_ASD_CLASS_H
