//
// Created by Julian on 25.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHGENERATOR_HPP
#define DEC_ISIONTREE_GRAPHGENERATOR_HPP

#include "Node.hpp"
#include <fstream>

class N {
  std::unordered_map<std::string, std::shared_ptr<N>> nodes;
};

using std::ofstream;

class GraphGenerator {
 public:
  GraphGenerator() = delete;
  GraphGenerator(const Node& root, const std::vector<std::string> labels, const std::string filepath="../graph.dot");
  ~GraphGenerator() = default;

 private:
  const std::vector<std::string> labels_;

  void generate(std::shared_ptr<Node> root, const std::string& filepath);
  void traverseTree(std::shared_ptr<Node> node, std::ofstream &file);

};

#endif //DEC_ISIONTREE_GRAPHGENERATOR_HPP
