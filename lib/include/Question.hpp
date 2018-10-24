//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_QUESTION_HPP
#define DEC__ISIONTREE_QUESTION_HPP

#include <vector>
#include <string>

using VecS = std::vector<std::string>;

class Question {
 public:
  Question();
  Question(const int column, const std::string value);

  const bool match(VecS example) const;
  const bool isNumeric(std::string value) const;
  const std::string toString(const VecS& labels) const;
  int column_;
  std::string value_;
};

#endif //DEC__ISIONTREE_QUESTION_HPP
