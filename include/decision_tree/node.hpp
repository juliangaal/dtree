//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_NODE_HPP
#define DECISIONTREE_NODE_HPP

#include <decision_tree/question.hpp>
#include <memory>
#include <optional>
#include <unordered_map>
#include <decision_tree/helpers.hpp>

namespace decision_tree {

class Node {
public:
    Node() = delete;

    explicit Node(const decision_tree::Data &data);

    Node(const Node &true_branch, const Node &false_branch, const Question &question);

    ~Node() = default;

public:
    inline const std::shared_ptr<Node> trueBranch() const { return true_branch_; }

    inline const std::shared_ptr<Node> falseBranch() const { return false_branch_; }

    inline const std::optional<Question> &question() const { return question_; }

    inline const std::optional<decision_tree::ClassCounter> &predictions() const { return predictions_; }

    inline bool predicts() const { return predictions_ != std::nullopt; }

private:
    std::shared_ptr<Node> true_branch_;
    std::shared_ptr<Node> false_branch_;
    std::optional<Question> question_;
    std::optional<decision_tree::ClassCounter> predictions_;
};

} // namespace decision_tree;

#endif //DECISIONTREE_NODE_HPP
