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

#include <dtree/node.h>
#include <dtree/calculations.h>
#include <utility>
#include <chrono>

using namespace dtree;

Node::Node(const Data &data)
        : true_branch_{}, false_branch_{}, question_{}, predictions_{calculations::class_counts(data)} {}

Node::Node(std::unique_ptr<Node> true_branch, std::unique_ptr<Node> false_branch, Question question) :
        true_branch_{std::move(true_branch)},
        false_branch_{std::move(false_branch)},
        question_{std::move(question)},
        predictions_{} {}
        
size_t Node::hash(const VecS &labels) const {
    if (predicts()) return 0;
    size_t hash = 0;
    if (true_branch_ && !true_branch_->predicts()) {
        hash += true_branch_->hash(labels);
    }
    return (hash +
            std::hash<std::unique_ptr<Node>>{}(true_branch_) +
            std::hash<std::unique_ptr<Node>>{}(false_branch_));
}
