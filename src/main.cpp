
//
// Created by prf on 04/03/19.
//

#include <iostream>
#include "List/ArrayList.h"



int test_ArrayList(){
    // TODO: add complete test suite
    ArrayList<int> lst(3);
    lst.add(1,1);
    lst.add(2,2);
    lst.add(3,3);
    ArrayList<int> lst2(lst);
    lst2.add(100, 2);
    lst2.add(-23,3);
    lst2.add(-1,1);
    lst2.add(-2000,lst2.size());
    std::cout << "list#1:" <<lst << std::endl;
    std::cout << "list#2:" <<lst2 << std::endl;
    lst.add(100,4);

    ArrayList<int> elst;

    elst.add(100,1);
    elst.remove(1);
    std::cout << "list#3 empty?:" << elst.is_empty() << std::endl;
    elst.remove(1);

    lst2.remove(3);
    lst2.remove(lst2.size());
    std::cout << "list#2:" <<lst2 << std::endl;

    return 0;
}
int main(){
    test_ArrayList();

    return 0;
}
