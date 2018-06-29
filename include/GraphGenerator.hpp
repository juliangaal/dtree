//
// Created by Julian on 25.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHGENERATOR_HPP
#define DEC_ISIONTREE_GRAPHGENERATOR_HPP

#include "Node.hpp"
#include <fstream>

using std::ofstream;

enum GraphType { SIMPLE, VERBOSE };

class GraphGenerator {
 public:
  GraphGenerator() = delete;
  GraphGenerator(const Node& root, const vector<string> labels, 
                 const GraphType type, const string filepath="../graph.dot");
  ~GraphGenerator() = default;

 private:
  const vector<string> labels;
  const GraphType graph_type;

  void generate(shared_ptr<Node> root, const string& filepath);
  void parseTree(shared_ptr<Node> node, ofstream &file);
  void parseSimpleTree(shared_ptr<Node> node, ofstream &file);
  void parseVerboseTree(shared_ptr<Node> node, ofstream &file);

};

#endif //DEC_ISIONTREE_GRAPHGENERATOR_HPP
