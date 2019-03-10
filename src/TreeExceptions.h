//
// Created by prf on 10/03/19.
//

#ifndef STRUTTURE_ASD_TREEEXCEPTIONS_H
#define STRUTTURE_ASD_TREEEXCEPTIONS_H

#include <stdexcept>

class NullNode : public std::invalid_argument {
    NullNode() : invalid_argument(
        "Node argument is null.") {};
};

class FullSize : public std::invalid_argument {
    FullSize() : invalid_argument(
        "Full size reached.") {};
};

class RootExists : public std::domain_error {
    RootExists() : domain_error(
        "Tree has already a root.") {};
};

class EmptyTree : public std::domain_error {
    EmptyTree() : domain_error(
        "Empty Tree.") {};
};

class NodeExists : public std::domain_error {
    NodeExists() : domain_error(
        "Node have already a child.") {};
};


#endif //STRUTTURE_ASD_TREEEXCEPTIONS_H
