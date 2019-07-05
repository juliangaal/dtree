//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DECISIONTREE_HPP
#define DECISIONTREE_DECISIONTREE_HPP

#include <decision_tree/dataset.hpp>
#include <decision_tree/node.hpp>
#include <decision_tree/calculations.hpp>
#include <decision_tree/data_reader.hpp>
#include <decision_tree/graph_generator.hpp>
#include <decision_tree/validation.hpp>
#include <decision_tree/helpers.hpp>

namespace decision_tree {

class DecisionTree {
public:
    DecisionTree() = delete;

    explicit DecisionTree(const Dataset &d);

    void print_tree() const;

    void test() const;

    void generateGraph(const std::string filepath) const;

    inline const decision_tree::Data &testingData() { return dr.testingData(); }

    inline const std::unique_ptr<Node> &root() { return root_; }

private:
    decision_tree::DataReader dr;

    std::unique_ptr<Node> buildTree(const decision_tree::Data &rows);

    void print_node(const std::unique_ptr<Node> &root, std::string spacing = "") const;

    std::unique_ptr<Node> root_;
};

} // namespace decision_tree

#endif //DECISIONTREE_DECISIONTREE_HPP
