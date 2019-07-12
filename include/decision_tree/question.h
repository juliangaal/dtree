//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_QUESTION_H
#define DECISIONTREE_QUESTION_H

#include <string>
#include <decision_tree/help.h>

namespace decision_tree {

class Question {
public:
    Question();

    Question(int column, std::string value);

    [[nodiscard]]
    bool match(const VecS &example) const;

    [[nodiscard]]
    const bool isNumeric(const std::string &value) const;

    [[nodiscard]]
    std::string toString(const VecS &labels) const;

    int column_;
    std::string value_;
};

} // namespace decision_tree

#endif //DECISIONTREE_QUESTION_H
