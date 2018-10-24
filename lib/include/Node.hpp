//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_NODE_HPP
#define DEC__ISIONTREE_NODE_HPP

#include "Question.hpp"
#include "Leaf.hpp"
#include <memory>

class Node {
 public:
  Node();
  explicit Node(Leaf l);
  Node(const Node& true_branch, const Node& false_branch, const Question &question);
  virtual ~Node() = default;

 public:
  const std::shared_ptr<Node> trueBranch() const { return true_branch_; }
  const std::shared_ptr<Node> falseBranch() const { return false_branch_; }
  const Question& question() const { return question_; }
  const std::shared_ptr<Leaf> leaf() const { return leaf_; }
 private:
  std::shared_ptr<Node> true_branch_;
  std::shared_ptr<Node> false_branch_;
  Question question_;
  std::shared_ptr<Leaf> leaf_;
};

#endif //DEC__ISIONTREE_NODE_HPP
