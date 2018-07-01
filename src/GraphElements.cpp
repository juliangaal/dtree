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

string GraphElement::result(const unordered_map<string, int> &data, branch branch) {
  static int id = 0;
  string result = "\"";// + std::to_string(id++) + "\\nvalues: ";
  double sum = Helper::tree::mapValueSum(data);
  size_t map_size = data.size();
  size_t counter = 1;

  string classification{};
  for (const auto& [k, v]: data) {
    classification += k + ": " + std::to_string(static_cast<int>(v / sum * 100)) + "% ";
    if (counter++ < map_size)
      classification += "\\n ";
  }
  result += classification;

  string values = "\\nvalues: ";
  for (const auto&
  [k, v]: data) {
    values += std::to_string(v) + " ";
  }

  result += values;

  string result_id = "\\nid: " + std::to_string(id++);
  result += result_id;

  string result_box = "   " + result + "\" [shape=box];\n";
  string label = "\"" + (branch == true ? GraphElement::label("True") : GraphElement::label("False"));
  result += label;

  result += result_box;
  return result;
}
