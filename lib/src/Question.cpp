//
// Created by Julian on 24.06.18.
//

#include "Question.hpp"
#include "Helper.hpp"

Question::Question() : column_(0), value_("") {}

Question::Question(const int column, const string value) : column_(column), value_(value) {}

const bool Question::match(VecS example) const {
  const string& val = example[column_];
  if (isNumeric(val)) {
    return std::stod(val) >= std::stod(value_);
  } else {
    return val == value_;
  }
}
const string Question::toString(const VecS& labels) const {
  string condition = "==";
  if (isNumeric(value_))
    condition = ">=";
  return "Is " + labels[column_] + " " + condition + " " + value_ + "?";
}

const bool Question::isNumeric(std::string value) const {
  double parsed_number = 0.0;

  if (bool empty = value.empty(); !empty) {
    try {
      parsed_number = std::stod(value);
      return true;
    } catch (const std::exception &e) {
      return false;
    }
  }
  return false;
}
