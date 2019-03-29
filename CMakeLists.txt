cmake_minimum_required(VERSION 3.13)
project(strutture_asd)

set(CMAKE_CXX_STANDARD 11)

add_executable(strutture_asd src/List/List.h src/List/ArrayList.h src/main.cpp src/List/LinkedList.h src/Stack/Stack.h src/Queue/Queue.h src/BinaryTree/BinTree.h src/BinaryTree/ArrayBinTree.h src/BinaryTree/LinkedBinTree.h src/TreeExceptions.h src/Tree/Tree.h src/Tree/LinkedTree.h src/Graph/Graph.h src/Graph/ListGraph.h src/PriorityQueue/PriorityQueue.h src/PriorityQueue/Heap.h)