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

#ifndef DTREE_DTREE_HPP
#define DTREE_DTREE_HPP

#include <dtree/dataset.h>
#include <dtree/node.h>
#include <dtree/calculations.h>
#include <dtree/data_reader.h>
#include <dtree/generate.h>
#include <dtree/validation.h>
#include <dtree/help.h>
#include <atomic>

namespace dtree {

class DecisionTree {
public:
    DecisionTree() = delete;

    explicit DecisionTree(const TrainingSet &trainset, const TestingSet &testset, LaunchType launch_type = BLOCKING);

    void print_tree() const;

    void test() const;

    void generate_graph(const std::string &file) const;

    inline const dtree::Data &testing_data() { return dr.testing_data(); }

    inline const std::unique_ptr<Node> &root() { return root_; }

    inline size_t size() { return size_; }

private:
    dtree::DataReader dr;

    std::unique_ptr<Node> blocking_build_rec(const Data &rows);

    std::unique_ptr<Node> async_build_rec(const Data &rows);

    void rec_print_node(const std::unique_ptr<Node> &root, std::string &spacing) const;

    std::atomic<size_t> size_;

    std::unique_ptr<Node> root_;
};

} // namespace dtree

#endif //DTREE_DTREE_HPP
