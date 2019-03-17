//
// Created by prf on 10/03/19.
//

#ifndef STRUTTURE_ASD_TREEEXCEPTIONS_H
#define STRUTTURE_ASD_TREEEXCEPTIONS_H

#include <stdexcept>

class NullNode : public std::invalid_argument {
public:
    NullNode() : invalid_argument(
        "Node argument is null.") {};
};

class FullSize : public std::invalid_argument {
public:
    FullSize() : invalid_argument(
        "Full size reached.") {};
};

class RootExists : public std::domain_error {
public:
    RootExists() : domain_error(
        "Tree has already a root.") {};
};

class EmptyTree : public std::domain_error {
public:
    EmptyTree() : domain_error(
        "Empty Tree.") {};
};

class NodeExists : public std::domain_error {
public:
    NodeExists() : domain_error(
        "Node have already a child.") {};
};

class NoSiblingAllowed : public std::domain_error {
public:
    NoSiblingAllowed() : domain_error(
            "Node can't have a sibling") {};
};


#endif //STRUTTURE_ASD_TREEEXCEPTIONS_H
