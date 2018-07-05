//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_QUESTION_HPP
#define DEC__ISIONTREE_QUESTION_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;
using VecS = vector<string>;

class Question {
 public:
  Question();
  Question(const int column, const string value);

  const bool match(VecS example) const;
  const bool isNumeric(std::string value) const;
  const string toString(const VecS& labels) const;
  int column_;
  string value_;
};

#endif //DEC__ISIONTREE_QUESTION_HPP
