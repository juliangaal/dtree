//
// Created by Julian on 24.06.18.
//

#ifndef DTREE_DTREE_HPP
#define DTREE_DTREE_HPP

#include <dtree/dataset.h>
#include <dtree/node.h>
#include <dtree/calculations.h>
#include <dtree/data_reader.h>
#include <dtree/generate.h>
#include <dtree/validation.h>
#include <dtree/help.h>

namespace dtree {

class DecisionTree {
public:
    DecisionTree() = delete;

    explicit DecisionTree(const TrainingSet &trainset, const TestingSet &testset);

    void print_tree() const;

    void test() const;

    void generate_graph(const std::filesystem::path &file) const;

    inline const dtree::Data &testing_data() { return dr.testing_data(); }

    inline const std::unique_ptr<Node> &root() { return root_; }

private:
    dtree::DataReader dr;

    std::unique_ptr<Node> build_tree(const Data &rows);

    void rec_print_node(const std::unique_ptr<Node> &root, std::string &spacing) const;

    size_t size_;

    std::unique_ptr<Node> root_;
};

} // namespace dtree

#endif //DTREE_DTREE_HPP
