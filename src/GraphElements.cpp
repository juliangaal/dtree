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

string GraphElement::result(const unordered_map<string, int> &data, branch b) {
  static int id = 0;
  string result = "\"";
  double sum = Helper::tree::mapValueSum(data);
  size_t map_size = data.size();
  size_t counter = 1;

  for (const auto& [k, v]: data) {
    result += k + ": " + std::to_string(static_cast<int>(v / sum * 100)) + "% ";
    if (counter++ < map_size)
      result += "\\n ";
  }

  result += "\\nvalues: ";

  for (const auto&
  [k, v]: data) {
    result += std::to_string(v) + " ";
  }

  result += "\\nid: " + std::to_string(id++);
  result += "\"" + (b ? GraphElement::label("True") : GraphElement::label("False"));
  result += "   " + result + "\" [shape=box];\n";
  return result;
}
