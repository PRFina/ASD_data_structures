//
// Created by prf on 04/03/19.
//

#ifndef STRUTTURE_ASD_LIST_H
#define STRUTTURE_ASD_LIST_H

#include <ostream>

/**
 * This class models a list Abstract Data Type. A list is a linear sequence with
 * an order relation defined on its elements.
 *
 * This class is an abstract class to provide an unified and consistent interface to client code.
 *
 * @tparam T type of the values contained in the list.
 * @tparam P type of the position used to scan and access the list.
 */
template <class T, class P>
class List {

public:
    typedef  T value_type;
    typedef  P position;

    /**
     * Get the k-th element in the specified position
     * @param pos position of the k-th element to retrieve
     * @return the k-th element
     */
    virtual value_type get(position pos) const =0;
    /**
     * Add an element to the list in the specified position.
     * All elements after the position will be shifted to the right
     * @param val element to add
     * @param pos position in which insert the element
     */
    virtual void add(const value_type& val, position pos) =0;
    /**
      * Update the value of the element in the specified position.
      * @param val value of the element to update
      * @param pos position in which insert the element
      */
    virtual void update(const value_type& v, position pos) =0;
    /**
     * Remove an element from the list in the specified position.
     * All elements after the position will be shifted to the left
     * @param pos position of the element to remove
     */
    virtual void remove(position pos) =0;
    /**
     *
     * @return position of the first element of the list
     */
    virtual position begin() const =0;
    /**
     * Check if the given position is the end of the list.
     * Note that list's end position isn't the same of the list's last element position.
     * @param
     * @return true if pos is the end of the list, false otherwise.
     */
    virtual bool end(position pos) const =0;
    /**
     *
     * @param pos of the element
     * @return the position of the previous element at position pos
     */
    virtual position previous(position pos) const =0;
    /**
     *
     * @param pos of the element
     * @return the position of the previous element at position pos
     */
    virtual position next(position pos) const =0; // returns the next position
    /**
     * Check if list have no elements
     * @return true if list is empty, false otherwise
     */
    virtual bool is_empty() const =0; // true if the list's size is 0
    /**
     * Get the number of elements in the list, that is the list's length
     * @return the length of the list
     */
    virtual unsigned int size() const =0; // true if the list's size is 0

};

template< class T, class P >
std::ostream& operator<<(std::ostream& os, const List<T,P> &list){
    os << "[";

    typename List<T,P>::position pos;
    pos = list.begin();

    while(!list.end(pos)){
        if(pos != list.begin())
            os <<  ", " << list.get(pos);
        else
            os << list.get(pos);
        pos = list.next(pos);
    }

    os << "]";

    return os;
}

#endif //STRUTTURE_ASD_LIST_H
