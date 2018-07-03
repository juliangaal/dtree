//
// Created by Julian on 25.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHGENERATOR_HPP
#define DEC_ISIONTREE_GRAPHGENERATOR_HPP

#include "Node.hpp"
#include <fstream>

using std::ofstream;

class GraphGenerator {
 public:
  GraphGenerator() = delete;
  GraphGenerator(const Node& root, const vector<string> labels, const string filepath="../graph.dot");
  ~GraphGenerator() = default;

 private:
  const vector<string> labels;

  void generate(shared_ptr<Node> root, const string& filepath);
  void traverseTree(shared_ptr<Node> node, ofstream &file);

};

#endif //DEC_ISIONTREE_GRAPHGENERATOR_HPP
