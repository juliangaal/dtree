//
// Created by Julian on 29.06.18.
//

#include "GraphElements.hpp"
#include "Helper.hpp"

string GraphElement::label(const string &label) {
  return "[label=\"" + label + "\"];\n";
}

string GraphElement::node(const string& question) {
  return "\"" + question + "\"";
}

string GraphElement::box(const string &label) {
  string box = node(label) + " [shape=box];\n   ";
  return box + node(label);
}

string GraphElement::leaf(const unordered_map<string, int>& data) {
  return result(data) + " [style=filled, color=\"1 0.8 1\"];\n";
}

string GraphElement::result(const unordered_map<string, int>& data) {
  string result = "\"";
  double sum = Helper::tree::mapValueSum(data);
  size_t map_size = data.size();
  size_t counter = 1;

  for (const auto& [k, v]: data) {
    result += k + ": " + std::to_string(v / sum * 100) + "% ";
    if (counter++ < map_size)
      result += "\\n ";
  }
  return result += "\"";
}

string GraphElement::verbose::node(const string& label, const double& gain) {
  string verbose_node = "\"" + label + "\\n";
  verbose_node += "gain: " + std::to_string(gain) + "\\n";
  verbose_node += "samples:\\n";
  verbose_node += "split:\\n\"";
  return verbose_node;
}

string GraphElement::verbose::box(const string &label, const double& gain) {
  string box = GraphElement::verbose::node(label, gain) + " [shape=box];\n   ";
  return box + GraphElement::verbose::node(label, gain);
}

string GraphElement::verbose::result(const unordered_map<string, int>& data) {
  string result = "\"";
  double sum = Helper::tree::mapValueSum(data);
  size_t map_size = data.size();
  size_t counter = 1;

  for (const auto& [k, v]: data) {
    result += k + ": " + std::to_string(v / sum * 100) + "% ";
    if (counter++ < map_size)
      result += "\\n ";
  }
  return result += "\"";
}

