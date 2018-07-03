//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_LEAF_HPP
#define DEC__ISIONTREE_LEAF_HPP

#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

using Data = vector<vector<string>>;
using ClassCounter = unordered_map<string, int>;

class Leaf {//: public Node {
 public:
  Leaf() = delete;
  Leaf(ClassCounter cc);// : predictions_(classCounts(rows)) {}
  virtual ~Leaf() = default;
// private:
  const ClassCounter predictions_;
};

#endif //DEC__ISIONTREE_LEAF_HPP
