//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_NODE_HPP
#define DEC__ISIONTREE_NODE_HPP

#include "Question.hpp"
#include "Leaf.hpp"
#include <memory>

using std::shared_ptr;
using std::make_shared;

class Node {
 public:
  Node();
  Node(Leaf l);
  Node(Node& true_branch, Node& false_branch, Question question);
  virtual ~Node() = default;
  shared_ptr<Node> true_branch_;
  shared_ptr<Node> false_branch_;
  Question question_;
  shared_ptr<Leaf> leaf_;
};

#endif //DEC__ISIONTREE_NODE_HPP
