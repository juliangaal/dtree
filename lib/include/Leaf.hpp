//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_LEAF_HPP
#define DEC__ISIONTREE_LEAF_HPP

#include <vector>
#include <string>
#include <unordered_map>

using Data = std::vector<std::vector<std::string>>;
using ClassCounter = std::unordered_map<std::string, int>;

class Leaf {//: public Node {
 public:
  Leaf() = delete;
  explicit Leaf(const ClassCounter cc);// : predictions_(classCounts(rows)) {}
  virtual ~Leaf() = default;

  inline const ClassCounter predictions() const { return predictions_; }

 private:
  const ClassCounter predictions_;
};

#endif //DEC__ISIONTREE_LEAF_HPP
