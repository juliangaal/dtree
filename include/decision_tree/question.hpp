//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_QUESTION_HPP
#define DECISIONTREE_QUESTION_HPP

#include <vector>
#include <string>
#include <decision_tree/helpers.hpp>

namespace decision_tree {

class Question {
public:
    Question();

    Question(int column, std::string value);

    const bool match(VecS example) const;

    const bool isNumeric(std::string value) const;

    const std::string toString(const VecS &labels) const;

    int column_;
    std::string value_;
};

} // namespace decision_tree

#endif //DECISIONTREE_QUESTION_HPP
