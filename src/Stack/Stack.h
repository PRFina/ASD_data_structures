//
// Created by prf on 05/03/19.
//

#ifndef STRUTTURE_ASD_STACK_H
#define STRUTTURE_ASD_STACK_H

#include <ostream>
#include "../List/LinkedList.h"

//Forward declaration for operator<< "non template" compilation error
template <class T>
class Stack;

template <class T>
std::ostream &operator<< (std::ostream &os, const Stack<T> &stack);
template <class T>
class Stack {
public:
    typedef typename LinkedList<T>::value_type value_type;
    Stack();
    Stack(const Stack<T>& stack);

    void push(const value_type& value);
    void pop();
    value_type top();

    std::size_t size();
    bool is_empty();

    friend std::ostream &operator<< <T>(std::ostream &os, const Stack<T> &stack);


private:
    LinkedList<T> _list;

};

template<class T>
Stack<T>::Stack() {
    _list;
}

template<class T>
Stack<T>::Stack(const Stack<T> &stack): _list(stack._list){}

template<class T>
void Stack<T>::push(const value_type &value) {
    _list.pushBack(value);
}

template<class T>
void Stack<T>::pop() {
    if (!is_empty())
        _list.popBack();
}

template<class T>
typename Stack<T>::value_type Stack<T>::top() {
    if(!is_empty())
        return _list.get(_list.last());
}

template<class T>
std::size_t Stack<T>::size() {
    return _list.size();
}

template<class T>
bool Stack<T>::is_empty() {
    return _list.is_empty();
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {

    if (!stack._list.is_empty()){
        typename LinkedList<T>::position pos = stack._list.last();
        os << stack._list.get(pos);
        os << " <-" << std::endl;
        pos = stack._list.previous(pos) ;
        while(!stack._list.end(pos)){
            os << stack._list.get(pos) << std::endl;
            pos = stack._list.previous(pos);
        }
    }
    else
        os << "{Ø}";


    return os;
}

#endif //STRUTTURE_ASD_STACK_H
