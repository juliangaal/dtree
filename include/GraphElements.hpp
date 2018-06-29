//
// Created by Julian on 29.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHELEMENTS_HPP
#define DEC_ISIONTREE_GRAPHELEMENTS_HPP

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace GraphElement {

string label(const string &label);

string box(const string &label);

string leaf(const unordered_map<string, int>& data);

string node(const string &question);

string result(const unordered_map<string, int>& data);

}

#endif //DEC_ISIONTREE_GRAPHELEMENTS_HPP
