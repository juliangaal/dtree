//
// Created by Julian on 24.06.18.
//

#include <decision_tree/question.hpp>
#include <decision_tree/helpers.hpp>

using namespace decision_tree;
using std::string;

Question::Question() : column_(0), value_("") {}

Question::Question(const int column, const string value) : column_(column), value_(value) {}

const bool Question::match(VecS example) const {
    const string &val = example[column_];
    if (isNumeric(val)) {
        return std::stod(val) >= std::stod(value_);
    } else {
        return val == value_;
    }
}

const string Question::toString(const VecS &labels) const {
    string condition = "==";
    if (isNumeric(value_))
        condition = ">=";
    return "Is " + labels[column_] + " " + condition + " " + value_ + "?";
}

const bool Question::isNumeric(std::string value) const {
    if (!value.empty()) {
        try {
            std::stod(value);
        } catch (const std::exception &e) {
            return false;
        }
    }
    return true;
}