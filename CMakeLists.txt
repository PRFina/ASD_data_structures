cmake_minimum_required(VERSION 3.13)
project(strutture_asd)

set(CMAKE_CXX_STANDARD 11)

add_executable(strutture_asd src/List/List.h src/List/ArrayList.h src/main.cpp src/List/LinkedList.h src/Stack/Stack.h src/Queue/Queue.h src/BinaryTree/BinTree.h src/BinaryTree/ArrayBinTree.h)