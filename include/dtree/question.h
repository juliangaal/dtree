//
// Created by Julian on 24.06.18.
//

#ifndef DTREE_QUESTION_H
#define DTREE_QUESTION_H

#include <string>
#include <dtree/help.h>

namespace dtree {

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

} // namespace dtree

#endif //DTREE_QUESTION_H
