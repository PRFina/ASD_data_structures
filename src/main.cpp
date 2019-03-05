
//
// Created by prf on 04/03/19.
//

#include <iostream>
#include "List/ArrayList.h"
#include "List/LinkedList.h"
using std::cout;
using std::endl;

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


int test_LinkedList(){

    LinkedList<int> lst;
    lst.pushFront(1000);
    lst.pushFront(200);
    lst.pushFront(80);
    cout << "List#1: " <<lst<< endl;

    LinkedList<int> lst2;
    lst2.pushBack(1000);
    lst2.pushBack(200);
    lst2.pushBack(80);
    cout << "List#2: " <<lst2 << endl;

    lst2.remove(lst2.begin());
    lst2.remove(lst2.begin());
    lst2.remove(lst2.begin());
    bool v = lst2.is_empty(); // -> True
    lst2.remove(lst2.begin());
    cout << "List#2: " << lst2 << endl;

    LinkedList<int> lst3;
    lst3.pushBack(10);
    lst3.pushBack(100);
    lst3.pushBack(1000);
    cout << "List#3: " << lst3 << endl;
    lst3.popFront();
    lst3.popBack();
    cout << "List#3: " << lst3 << endl; // ->[100]

    LinkedList<int> lst4(lst);
    cout << "List#4: " << lst4 << endl;
    lst4.clear();
    //Check if lst4 isn't a shallowed copy of lst3
    cout << "List#4: " << lst4 << endl;
    cout << "List#3: " << lst3 << endl;

    LinkedList<std::string> lst5("Hello World", 10);
    cout << "List#5: " << lst5 << endl;
    LinkedList<std::string> lst6(lst5);
    cout << "List#5: " << lst5 << endl;
    cout << "List#6: " << lst6 << endl;
    cout << "List#5 == List#6?: " << std::boolalpha <<(lst5 == lst6) << endl;

    lst6.popBack();
    cout << "List#5: " << lst5 << endl;
    cout << "List#6: " << lst6 << endl;
    cout << "List#5 == List#6?: " << std::boolalpha <<(lst5 == lst6) << endl;

    lst5.popBack();
    lst6.update("Changed Value",lst6.begin());
    cout << "List#5: " << lst5 << endl;
    cout << "List#6: " << lst6 << endl;
    cout << "List#5 == List#6?: " << std::boolalpha <<(lst5 == lst6) << endl;

    lst2.pushBack(444);
    lst2.pushBack(555);
    lst2.pushBack(666);
    cout << "List#2: " << lst2 << endl;
    cout << "List#3: " << lst3 << endl;
    lst3 = lst2; // -> lst3 = [ 444,555,666]
    lst2.pushBack(777);
    cout << "List#2: " << lst2 << endl;
    cout << "List#3: " << lst3 << endl;

    return 0;
}

int main(){
    //test_ArrayList();
    test_LinkedList();

    return 0;
}
