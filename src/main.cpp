
//
// Created by prf on 04/03/19.
//

#include <iostream>
#include "List/ArrayList.h"
#include "List/LinkedList.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "assert.h"

using std::cout;
using std::endl;

void print_title(std::string test_title){
    cout << endl << endl << "******************* " << test_title << " *******************" << endl << endl;
}

int test_ArrayList(){
    print_title("TEST ARRAY LIST");
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
    print_title("TEST LINKED LIST");
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


int test_Stack(){
    print_title("TEST STACK");

    Stack<int> stk1;
    stk1.push(1);
    stk1.push(2);
    stk1.push(3);
    stk1.push(4);
    stk1.push(5);
    cout << std::boolalpha << "Stack#1 is empty?: " << stk1.is_empty() << endl;
    cout << "Stack#1 size: " << stk1.size() << endl;

    cout << "Stack#1 top: " << stk1.top() << endl;
    stk1.pop();
    cout << "Stack#1 top: " << stk1.top() << endl;
    stk1.pop();
    cout << "Stack#1 top: " << stk1.top() << endl;

    Stack<int> stk2(stk1);
    stk1.pop();
    cout << "Stack#1 top: " << stk1.top() << endl;
    stk1.pop();
    cout << "Stack#1 top: " << stk1.top() << endl;
    stk1.pop();
    cout << std::boolalpha << "Stack#1 is empty?: " << stk1.is_empty() << endl;
    cout << "Stack#1 size: " << stk1.size() << endl;

    cout << stk2;
    cout << "Stack#2 top:" << stk2.top() << endl;
    stk2.pop();
    cout << "Stack#2 top:" << stk2.top() << endl;
    cout << stk2;
    stk2.pop();
    cout << "Stack#2 top:" << stk2.top() << endl;
    cout << stk2;
    stk2.pop();
    cout << "Stack#2 top:" << stk2.top() << endl;
    cout << stk2;




}

int test_Queue(){
    print_title("TEST QUEUE");
    Queue<int> que1;
    que1.push(10);
    que1.push(20);
    que1.push(30);
    que1.push(40);
    cout << que1 << endl;

    cout << "Queue#1 is empty?: " << std::boolalpha << que1.is_empty() << endl; // -> false
    cout << "Queue#1 size: " << que1.size() << endl; // -> 4

    cout << "Queue#1 back: "<< que1.back() << endl; // -> 40
    cout << "Queue#1 front: "<< que1.front() << endl; // -> 10

    que1.pop();
    cout << que1 << endl;
    cout << "Queue#1 back: "<< que1.back() << endl; // -> 40
    cout << "Queue#1 front: "<< que1.front() << endl; // -> 20

    cout << "Queue#1 size: " << que1.size() << endl; // -> 3

    que1.pop();
    que1.pop();
    que1.pop();
    cout << que1 << endl;
    cout << "Queue#1 is empty?: " << std::boolalpha << que1.is_empty() << endl; // -> true
    cout << "Queue#1 size: " << que1.size() << endl; // -> 0


    return 0;
}


int main(){
    test_ArrayList();
    test_LinkedList();
    test_Stack();
    test_Queue();




    return 0;
}
