//
// Created by Julian on 25.06.18.
//

#ifndef DECISIONTREE_GRAPHGENERATOR_HPP
#define DECISIONTREE_GRAPHGENERATOR_HPP

#include "node.hpp"
#include <fstream>

namespace decision_tree {

class GraphGenerator {
public:
    GraphGenerator() = delete;

    GraphGenerator(const Node &root, const std::vector<std::string> labels,
                   const std::string filepath = "../graph.dot");

    ~GraphGenerator() = default;

private:
    const std::vector<std::string> labels_;

    void generate(std::shared_ptr<Node> root, const std::string &filepath);

    void traverseTree(std::shared_ptr<Node> node, std::ofstream &file);

};

} // namespace decision_tree

#endif //DECISIONTREE_GRAPHGENERATOR_HPP
