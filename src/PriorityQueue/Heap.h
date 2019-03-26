//
// Created by prf on 21/03/19.
//

#ifndef STRUTTURE_ASD_HEAP_H
#define STRUTTURE_ASD_HEAP_H



#include <glob.h>
#include "PriorityQueue.h"

template <class T>
class Heap: public PriorityQueue<T> {
public:
    typedef typename PriorityQueue<T>::value_type value_type;

    Heap(const size_t expected_size=50);
    Heap(const Heap<T>& heap);

    void insert(const value_type& val) override;
    void remove(const value_type& val) override;

    value_type find_min() const override;
    void remove_min() override;

    bool is_empty() const  override;
    size_t get_size() const override;

    virtual ~Heap();

private:
    const static size_t _root = 0;
    value_type* _data;
    size_t _MAX_SIZE;
    size_t _last;

    size_t get_parent(size_t node) const;
    size_t get_left_child(size_t node) const;
    size_t get_right_child(size_t node) const;

    void fix_up(size_t node);
    void fix_down(size_t node);
    size_t argmin(const size_t& left, const size_t& right);
    bool is_leaf(const size_t& node) const;

};



template<class T>
Heap<T>::Heap(const size_t expected_size) {

    _MAX_SIZE = expected_size;
    _data = new value_type[_MAX_SIZE];
    _last = 0;

}

template<class T>
Heap<T>::Heap(const Heap<T> &heap) {
    _MAX_SIZE = heap._MAX_SIZE;
    _data = new value_type[_MAX_SIZE];

    for (int i = 0; i < heap._size; ++i) {
        _data[i] = heap._data[i];
    }
    _last = heap._last;
}

template<class T>
Heap<T>::~Heap() {
    _MAX_SIZE = 0;
    _last = 0;
    delete[] _data;
}

template<class T>
void Heap<T>::insert(const value_type& val) {
    if (_last < _MAX_SIZE) {

        _data[_last] = val;
        fix_up(_last);
        _last++;
    }

}

template<class T>
void Heap<T>::remove(const value_type& val) {

}

template<class T>
typename Heap<T>::value_type Heap<T>::find_min() const {
    return _data[_root];
}

template<class T>
void Heap<T>::remove_min() {
    if(!is_empty()){
        _data[0] = _data[_last-1];
        _last--;
        fix_down(_root);
    }

}

template<class T>
bool Heap<T>::is_empty() const  {
    return (_last == 0);
}

template<class T>
bool Heap<T>::is_leaf(const size_t &node) const {
    return(get_left_child(node) >= _last && get_right_child(node) >= _last);
}


template<class T>
size_t Heap<T>::get_size() const {
    return _last;
}

template<class T>
size_t Heap<T>::get_parent(const size_t node) const{
    if(node != _root)
        return (node-1)/2;
}

template<class T>
size_t Heap<T>::get_left_child(const size_t node) const{
    return 2*node+1;
}

template<class T>
size_t Heap<T>::get_right_child(const size_t node) const{
    return 2*node+2;
}

template<class T>
void Heap<T>::fix_up(size_t child) {
    size_t parent = get_parent(child);

    while ( child != _root && _data[child] < _data[parent]){
        std::swap(_data[child], _data[parent]);
        child = parent; //"climb the tree"
        parent = get_parent(child);
    }

}

template<class T>
void Heap<T>::fix_down(size_t node) {

    bool stop = false;
    while (!stop){
        size_t lowest_priority_child = argmin(get_left_child(node), get_right_child(node));

        if(_data[node] < _data[lowest_priority_child])
            break;

        std::swap(_data[node],_data[lowest_priority_child]);
        node = lowest_priority_child;

        if(is_leaf(lowest_priority_child))
            stop=true;
    }

}

template<class T>
size_t Heap<T>::argmin(const size_t &left, const size_t &right) {
    if(_data[left] <= _data[right])
        return left;

    return right;
}



#endif //STRUTTURE_ASD_HEAP_H
