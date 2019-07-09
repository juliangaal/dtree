//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_NODE_H
#define DECISIONTREE_NODE_H

#include <decision_tree/question.h>
#include <memory>
#include <optional>
#include <unordered_map>
#include <decision_tree/help.h>

namespace decision_tree {

class Node {
public:
    Node() = delete;

    explicit Node(const decision_tree::Data &data);

    Node(std::unique_ptr<Node> true_branch, std::unique_ptr<Node> false_branch, Question question);

    ~Node() = default;

public:
    inline const std::unique_ptr<Node> &true_branch() const { return true_branch_; }

    inline const std::unique_ptr<Node> &false_branch() const { return false_branch_; }

    inline const std::optional<Question> &question() const { return question_; }

    inline const std::optional<decision_tree::ClassCounter> &predictions() const { return predictions_; }

    inline bool predicts() const { return predictions_ != std::nullopt; }

    size_t hash(const VecS &labels) const;

private:
    std::unique_ptr<Node> true_branch_;
    std::unique_ptr<Node> false_branch_;
    std::optional<Question> question_;
    std::optional<decision_tree::ClassCounter> predictions_;
};

} // namespace decision_tree;

#endif //DECISIONTREE_NODE_H
