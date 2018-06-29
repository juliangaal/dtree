//
// Created by Julian on 24.06.18.
//

#include "Node.hpp"

Node::Node() : gain(0.0), true_branch_(nullptr), false_branch_(nullptr), leaf_(nullptr) {}

Node::Node(double gain, Leaf l) : gain(gain), leaf_(make_shared<Leaf>(l)) {}

Node::Node(double gain, Node& true_branch, Node& false_branch, Question question) :
    gain(gain),
    true_branch_(make_shared<Node>(true_branch)),
    false_branch_(make_shared<Node>(false_branch)),
    question_(question),
    leaf_(nullptr) {}
