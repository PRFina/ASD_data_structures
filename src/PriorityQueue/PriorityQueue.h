//
// Created by prf on 21/03/19.
//

#ifndef STRUTTURE_ASD_PRIORITYQUEUE_H
#define STRUTTURE_ASD_PRIORITYQUEUE_H

#include <glob.h>

template <class T>
class PriorityQueue {
public:
    typedef T value_type;

    virtual void insert(const value_type& val) =0;
    virtual void remove(const value_type& val) =0;

    virtual value_type find_min() const =0;
    virtual void remove_min() =0;

    virtual bool is_empty() const =0;
    virtual size_t get_size() const  =0;
};


#endif //STRUTTURE_ASD_PRIORITYQUEUE_H
