
//
// Created by prf on 04/03/19.
//

#include <iostream>
#include "List/ArrayList.h"
#include "List/LinkedList.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "assert.h"
#include "BinaryTree/ArrayBinTree.h"
#include "BinaryTree/LinkedBinTree.h"

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

int test_ArrayBinTree(){
    print_title("TEST BINARY TREE WITH ARRAY");
    typedef ArrayBinTree<int>::Node Node;

    ArrayBinTree<int> tree1;
    tree1.add_root(10000);

    tree1.add_left_child(100, tree1.get_root());
    tree1.add_right_child(-100, tree1.get_root());
    Node n1 = tree1.get_left_child(tree1.get_root());
    Node n2 = tree1.get_right_child(tree1.get_root());


    tree1.add_left_child(500, n1);
    Node n3 = tree1.get_left_child(n1);


    tree1.add_left_child(800, n3);
    tree1.add_right_child(-800, n3);
    Node n4 = tree1.get_left_child(n3);
    Node n5 = tree1.get_right_child(n3);

    tree1.add_left_child(50, n2);

    // Visit Tests
    cout << "PREVISIT:" << endl;
    tree1.pre_visit(tree1.get_root());
    cout <<  endl;

    cout << "INVISIT:" << endl;
    tree1.in_visit(tree1.get_root());
    cout <<  endl;

    cout << "POSTVISIT:" << endl;
    tree1.post_visit(tree1.get_root());
    cout <<  endl;

    cout << "BFSVISIT:" << endl;
    tree1.level_visit(tree1.get_root());
    cout <<  endl;

    // Height Tests
    cout << "Tree Height:" << endl;
    cout <<  tree1.get_height(tree1.get_root()) << endl;

    cout << "SubTree Height (right child of root):" << endl;
    cout <<  tree1.get_height(tree1.get_right_child(tree1.get_root())) << endl;

    cout << "SubTree Height rooted in a leaf node(left child of right child of root):" << endl;
    cout <<  tree1.get_height(tree1.get_left_child(tree1.get_right_child(tree1.get_root()))) << endl;
    cout << endl << endl;
    // Depth Tests
    cout << "Depth of root:" << endl;
    cout <<  tree1.get_depth(tree1.get_root()) << endl;

    cout << "Depth of right child of root:" << endl;
    cout <<  tree1.get_depth(tree1.get_right_child(tree1.get_root())) << endl;

    cout << "Sub Depth rooted in a lef node(left child of right child of root):" << endl;
    cout <<  tree1.get_depth(tree1.get_left_child(tree1.get_right_child(tree1.get_root()))) << endl << endl;


    cout << "Remove subtree roted in left child of root " << endl;
    tree1.remove(n1);
    tree1.add_left_child(2000,tree1.get_root());
    tree1.add_right_child(-2000,n1);

    cout << "PREVISIT:" << endl;
    tree1.pre_visit(tree1.get_root());
    cout <<  endl;

    cout << "INVISIT:" << endl;
    tree1.in_visit(tree1.get_root());
    cout <<  endl;

    cout << "POSTVISIT:" << endl;
    tree1.post_visit(tree1.get_root());
    cout <<  endl;

    cout << "NEW TREE WITH COPY CONSTRUCTOR";
    ArrayBinTree<int> tree2(tree1);

    cout << "PREVISIT:" << endl;
    tree2.pre_visit(tree2.get_root());
    cout <<  endl;

    tree2.add_left_child(666,tree2.get_left_child(tree2.get_root()));
    cout << "PREVISIT:" << endl;
    tree2.pre_visit(tree2.get_root());
    cout <<  endl;

    return 0;
}

int test_LinkedBinTree(){
    LinkedBinTree<int> T1(1000);

    T1.add_left_child(100,T1.get_root());
    T1.add_right_child(-100,T1.get_root());

    T1.add_left_child(500, T1.get_left_child(T1.get_root()));
    T1.add_left_child(50,T1.get_right_child(T1.get_root()));

    T1.add_left_child(800, T1.get_left_child(T1.get_left_child(T1.get_root())));
    T1.add_right_child(-800, T1.get_left_child(T1.get_left_child(T1.get_root())));

    cout << "T1 pre-order visit: ";
    T1.pre_visit(T1.get_root());
    cout << "T1 Height's: " << T1.get_height(T1.get_root()) << endl;



    LinkedBinTree<int> T2(T1);
    cout << "T2 (copied from T1) pre-order visit: ";
    T2.pre_visit(T2.get_root());
    cout << endl;




    T1.remove(T1.get_root());
    T1.add_root(8000);
    cout << "T1 after removed all nodes and added an new root (only one node) pre-order visit: ";
    T1.pre_visit(T1.get_root());
    int h = T1.get_height(T1.get_root());
    cout << "T1 Height's: " << h << endl;

    cout << "T2 add as right child to right child of root the subtree "
            "rooted in the left child of left child of root, resulted preorder visit:" << endl;

    T2.add_right_subtree(T2.get_left_child(T2.get_left_child(T2.get_root())), T2.get_right_child(T2.get_root()));
    T2.pre_visit(T2.get_root());

    LinkedBinTree<int> T3 = T2.extract_subtree(T2.get_right_child(T2.get_root()));


}
int main(){
    //test_ArrayList();
    //test_LinkedList();
    //test_Stack();
    //test_Queue();
    //test_ArrayBinTree();
    test_LinkedBinTree();





    return 0;
}
