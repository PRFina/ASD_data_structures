//
// Created by prf on 04/03/19.
//

#ifndef STRUTTURE_ASD_ARRAYLIST_H
#define STRUTTURE_ASD_ARRAYLIST_H

#include <exception>
#include <ostream>
#include "List.h"
// TODO: comment code, add complexity info
template <class T>
class ArrayList: public List<T, int>{
public:
    typedef typename List<T,int>::value_type value_type;
    typedef typename List<T,int>::position position;

    //Constructors
    ArrayList();
    ArrayList(unsigned int size);
    ArrayList(value_type val, unsigned int length);
    ArrayList(const ArrayList<T>& list);

    ~ArrayList();

    // Accessors
    bool is_empty() const override;
    unsigned int size() const override;
    value_type get(position pos) const override;

    // Modifiers
    void add(const value_type &v, position pos) override;
    void update(const value_type &v, position pos) override;
    void remove(position pos);

    position begin() const override;
    bool end(position pos) const override;
    int next(position pos) const override;
    int previous(position pos) const override;

    //Operators
    ArrayList<T>& operator=(const ArrayList<T>& other);
    bool operator==(const ArrayList &rhs) const;
    bool operator!=(const ArrayList &rhs) const;


private:
    value_type* _elements; // array of value_type elements
    unsigned int _length; // length of list
    unsigned int _size; //size of _elements array

    void resize(T*& array, unsigned int old_size, unsigned int new_size);
    bool in_range(position pos) const;


};

template<class T>
ArrayList<T>::ArrayList(): _size(25) {
    _elements = new value_type[_size];
    _length = 0;
}

template<class T>
ArrayList<T>::ArrayList(value_type val, unsigned int length): _size(length*2) {
    _elements = new value_type[_size];
    _length = length;

    for (int i=0; i < _length; i++)
        _elements[i] = val;
}

template<class T>
ArrayList<T>::ArrayList(unsigned int size): _size(size) {
    _elements = new value_type[_size];
    _length = 0;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& list) {
    _size = list._size;
    _length = list._length;
    _elements = new T[_size];

    for(int i=0; i < list._size; i++){
        _elements[i] = list._elements[i];
    }
}

template<class T>
ArrayList<T>::~ArrayList() {
    delete _elements;
}

template<class T>
bool ArrayList<T>::is_empty() const {
    return (_length == 0);
}

template<class T>
unsigned int ArrayList<T>::size() const {
    return _length;
}

template<class T>
typename ArrayList<T>::value_type ArrayList<T>::get(position pos) const {
    if (in_range(pos))
        return _elements[pos-1];
    else
        throw std::out_of_range("index is out of range");
}

template<class T>
void ArrayList<T>::add(const value_type &v, position pos) {

    if(_length == _size){ // array doubling
        resize(_elements, _size, _size * 2);
        _size *= 2;
    }


    if( 0 < pos && pos <= _length+1 ){ // pos <= _length+1, allow to append v to list
        for(int i = _length; i >= pos; i--) // shift to right
            _elements[i] = _elements[i-1];
        _elements[pos-1] = v;
        _length++;
    }
    else
        throw std::out_of_range("index is out of range");

}

template<class T>
void ArrayList<T>::update(const value_type &v, position pos) {
    if( in_range(pos))
        _elements[pos-1] = v;
    else
        throw std::out_of_range("index is out of range");
}

template<class T>
typename ArrayList<T>::position ArrayList<T>::begin() const {
    return 1; //list is 1-based index, ArrayList.get(ArrayList.begin()) => _elements[0]
}

template<class T>
bool ArrayList<T>::end(position pos) const {
    if ( 0 < pos && pos <= _length +1)
        return pos == _length + 1;
    else
        return false;
}

template<class T>
int ArrayList<T>::next(position pos) const {
    if ( 0 < pos && pos < _length+1)
        return pos+1;
    else
        return pos;
}

template<class T>
int ArrayList<T>::previous(position pos) const {
    if ( 1 < pos && pos < _length+1)
        return pos-1;
    else
        return pos;
}

template<class T>
void ArrayList<T>::remove(position pos) {
    // TODO: apply resizing strategy as explained in Demetrescu_Camil__Finocchi_Irene__Italiano_Giuseppe_-_Algoritmi_e_Strutture_Dati ch 3 pag 63
    if(is_empty())
        return; //remove on empty list have no effect
    if( in_range(pos)){
        for (int i = (pos-1); i < (_length-1); i++)
            _elements[i] = _elements[i+1];
        _length--;
    }
    else
        throw std::out_of_range("index is out of range");
}



template<class T>
void ArrayList<T>::resize(T*& array, unsigned int old_size, unsigned int new_size) {
    T* temp = new T[new_size];
    int elements_to_copy;

    if ( old_size < new_size)
        elements_to_copy = old_size;
    else
        elements_to_copy = new_size;

    for(int i=0; i < elements_to_copy; i++)
        temp[i] = array[i];

    delete[] array;
    array = temp;
}

template<class T>
bool ArrayList<T>::in_range(position pos) const {
    return ( 0 < pos && pos < _length+1);
}

template<class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other){
    if (this != other){
        _size = other._size;
        _length = other._length;

        delete _elements;
        _elements = new T[_size];

        for(int i=0; i < _length; i++)
            _elements[i] = other._elements[i];
    }
}

template<class T>
bool ArrayList<T>::operator==(const ArrayList &rhs) const {
    if (_length != rhs._length)
        return false;
    for(int i=0; i < _length; i++){
        if (_elements[i] != rhs._elements[i])
            return false;
    }
    return true;
}

template<class T>
bool ArrayList<T>::operator!=(const ArrayList &rhs) const {
    return !(rhs == *this);
}


#endif //STRUTTURE_ASD_ARRAYLIST_H
