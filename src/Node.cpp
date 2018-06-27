//
// Created by Julian on 24.06.18.
//

#include "Node.hpp"

Node::Node() : true_branch_(nullptr), false_branch_(nullptr), leaf_(nullptr) {}

Node::Node(Leaf l) : leaf_(make_shared<Leaf>(l)) {}

Node::Node(Node& true_branch, Node& false_branch, Question question) :
    true_branch_(make_shared<Node>(true_branch)),
    false_branch_(make_shared<Node>(false_branch)),
    question_(question),
    leaf_(nullptr) {}
