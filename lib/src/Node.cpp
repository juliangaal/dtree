//
// Created by Julian on 24.06.18.
//

#include "Node.hpp"

using std::make_shared;

Node::Node() : true_branch_(nullptr), false_branch_(nullptr), question_({}), leaf_(nullptr) {}

Node::Node(Leaf l) : true_branch_(nullptr), false_branch_(nullptr), question_({}), leaf_(make_shared<Leaf>(l)) {}

Node::Node(const Node &true_branch, const Node &false_branch, const Question &question) :
    true_branch_(make_shared<Node>(true_branch)),
    false_branch_(make_shared<Node>(false_branch)),
    question_(question),
    leaf_(nullptr) {}
