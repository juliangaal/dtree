//
// Created by Julian on 24.06.18.
//

#include <decision_tree/question.h>
#include <decision_tree/help.h>

using namespace decision_tree;
using std::string;

Question::Question() : column_{}, value_{} {}

Question::Question(int column, string value) : column_{column}, value_{std::move(value)} {}

bool Question::match(const VecS &example) const {
    const string &val = example[column_];

    try {
        // faster than calling isNumeric on both!
        return std::stod(val) >= std::stod(value_);
    } catch (const std::exception &e) {
        return val == value_;
    }
}

string Question::toString(const VecS &labels) const {
    string condition = "==";
    if (isNumeric(value_))
        condition = ">=";
    return "Is " + labels[column_] + " " + condition + " " + value_ + "?";
}

const bool Question::isNumeric(const string &value) const {
    try {
        std::stod(value);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}
