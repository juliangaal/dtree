//
// Created by Julian on 29.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHELEMENTS_HPP
#define DEC_ISIONTREE_GRAPHELEMENTS_HPP

#include <string>
#include <unordered_map>

using branch = bool;
using std::string;
using std::unordered_map;

namespace GraphElement {

string label(const string &label);

string box(const string &label);

string node(const string &question);

string result(const unordered_map<string, int> &data, branch b);

}

#endif //DEC_ISIONTREE_GRAPHELEMENTS_HPP
