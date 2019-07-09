//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DECISIONTREE_HPP
#define DECISIONTREE_DECISIONTREE_HPP

#include <decision_tree/dataset.h>
#include <decision_tree/node.h>
#include <decision_tree/calculations.h>
#include <decision_tree/data_reader.h>
#include <decision_tree/generate.h>
#include <decision_tree/validation.h>
#include <decision_tree/help.h>
#include <c++/8/filesystem>

namespace decision_tree {

class DecisionTree {
public:
    DecisionTree() = delete;

    explicit DecisionTree(const TrainingSet &trainset, const TestingSet &testset);

    void print_tree() const;

    void test() const;

    void generate_graph(const std::filesystem::path &file) const;

    inline const decision_tree::Data &testing_data() { return dr.testing_data(); }

    inline const std::unique_ptr<Node> &root() { return root_; }

private:
    decision_tree::DataReader dr;

    std::unique_ptr<Node> build_tree(const Data &rows);

    void rec_print_node(const std::unique_ptr<Node> &root, std::string spacing = "") const;

    size_t size_;

    std::unique_ptr<Node> root_;
};

} // namespace decision_tree

#endif //DECISIONTREE_DECISIONTREE_HPP
