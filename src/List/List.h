//
// Created by prf on 04/03/19.
//

#ifndef STRUTTURE_ASD_LIST_H
#define STRUTTURE_ASD_LIST_H

template <class T, class P>
class List {

public:
    typedef  T value_type;
    typedef  P position;

    virtual void create() =0;
    virtual bool is_empty() const =0; // true if the list's size is 0
    virtual unsigned int size() const =0; // true if the list's size is 0

    virtual value_type get(position) const =0;
    virtual void add(const value_type& v, position pos) =0; // insert an element
    virtual void update(const value_type& v, position pos) =0; // insert an element
    virtual void remove(position pos) =0; // delete the element at position pos

    virtual position begin() const =0;  // returns a position pointing to the beginning of the list
    virtual bool end(position) const =0; // returns a position pointing to the end of the list
    virtual position previous(position) const =0; // return the previous position
    virtual position next(position) const =0; // returns the next position



};


#endif //STRUTTURE_ASD_LIST_H
