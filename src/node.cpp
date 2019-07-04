//
// Created by Julian on 24.06.18.
//

#include <decision_tree/node.hpp>
#include <decision_tree/calculations.hpp>

using namespace decision_tree;
using std::make_shared;

Node::Node(const Data &data)
        : true_branch_{}, false_branch_{}, question_{}, predictions_{calculations::classCounts(data)} {}

Node::Node(const Node &true_branch, const Node &false_branch, const Question &question) :
        true_branch_{make_shared<Node>(true_branch)},
        false_branch_{make_shared<Node>(false_branch)},
        question_{question},
        predictions_{} {}
