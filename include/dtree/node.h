//
// Created by Julian on 24.06.18.
//

#ifndef DTREE_NODE_H
#define DTREE_NODE_H

#include <dtree/question.h>
#include <memory>
#include <optional>
#include <unordered_map>
#include <dtree/help.h>

namespace dtree {

class Node {
public:
    Node() = delete;

    explicit Node(const dtree::Data &data);

    Node(std::unique_ptr<Node> true_branch, std::unique_ptr<Node> false_branch, Question question);

    ~Node() = default;

public:
    inline const std::unique_ptr<Node> &true_branch() const { return true_branch_; }

    inline const std::unique_ptr<Node> &false_branch() const { return false_branch_; }

    inline const std::optional<Question> &question() const { return question_; }

    inline const std::optional<dtree::ClassCounter> &predictions() const { return predictions_; }

    inline bool predicts() const { return predictions_ != std::nullopt; }

    size_t hash(const VecS &labels) const;

private:
    std::unique_ptr<Node> true_branch_;
    std::unique_ptr<Node> false_branch_;
    std::optional<Question> question_;
    std::optional<dtree::ClassCounter> predictions_;
};

} // namespace dtree;

#endif //DTREE_NODE_H
