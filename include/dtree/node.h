/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *For more information, please refer to <http://unlicense.org>
*/

#ifndef DTREE_NODE_H
#define DTREE_NODE_H

#include <dtree/question.h>
#include <memory>
#include <optional>
#include <unordered_map>
#include <dtree/help.h>

namespace dtree {

class Node {
public:
    Node() = delete;

    explicit Node(const dtree::Data &data);

    Node(std::unique_ptr<Node> true_branch, std::unique_ptr<Node> false_branch, Question question);

    ~Node() = default;

public:
    inline const std::unique_ptr<Node> &true_branch() const { return true_branch_; }

    inline const std::unique_ptr<Node> &false_branch() const { return false_branch_; }

    inline const std::optional<Question> &question() const { return question_; }

    inline const std::optional<dtree::ClassCounter> &predictions() const { return predictions_; }

    inline bool predicts() const { return predictions_ != std::nullopt; }

    size_t hash(const VecS &labels) const;

private:
    std::unique_ptr<Node> true_branch_;
    std::unique_ptr<Node> false_branch_;
    std::optional<Question> question_;
    std::optional<dtree::ClassCounter> predictions_;
};

} // namespace dtree;

#endif //DTREE_NODE_H
