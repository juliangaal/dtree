//
// Created by Julian on 29.06.18.
//

#include <decision_tree/graph_elements.hpp>
#include <decision_tree/helpers.hpp>

using std::string;
using namespace decision_tree;

string graph_element::label(const string &label) {
    return "[label=\"" + label + "\"];\n";
}

string graph_element::node(const string &question) {
    return "\"" + question + "\"";
}

string graph_element::box(const string &label) {
    string box = node(label) + " [shape=box];\n   ";
    return box + node(label);
}

string graph_element::result(const std::unordered_map<string, int> &data, branch branch) {
    static int id = 0;
    string result = "\"";
    double sum = helpers::tree::mapValueSum(data);
    size_t map_size = data.size();
    size_t counter = 1;

    string classification{};
    for (const auto&[k, v]: data) {
        classification += k + ": " + std::to_string(static_cast<int>(v / sum * 100)) + "% ";
        if (counter++ < map_size)
            classification += "\\n ";
    }
    result += classification;

    string values = "\\nvalues: ";
    for (const auto&[k, v]: data) {
        values += std::to_string(v) + " ";
    }

    result += values;

    string result_id = "\\nid: " + std::to_string(id++);
    result += result_id;

    string result_box = "   " + result + "\" [shape=box];\n";
    string label = "\"" + (branch == true ? graph_element::label("True") : graph_element::label("False"));
    result += label;

    result += result_box;
    return result;
}
