//
// Created by Julian on 24.06.18.
//

#include <decision_tree/node.hpp>
#include <decision_tree/calculations.hpp>
#include <utility>

using namespace decision_tree;

Node::Node(const Data &data)
        : true_branch_{}, false_branch_{}, question_{}, predictions_{calculations::classCounts(data)} {}

Node::Node(std::unique_ptr<Node> true_branch, std::unique_ptr<Node> false_branch, Question question) :
        true_branch_{std::move(true_branch)},
        false_branch_{std::move(false_branch)},
        question_{std::move(question)},
        predictions_{} {}