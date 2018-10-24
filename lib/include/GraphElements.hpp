//
// Created by Julian on 29.06.18.
//

#ifndef DEC_ISIONTREE_GRAPHELEMENTS_HPP
#define DEC_ISIONTREE_GRAPHELEMENTS_HPP

#include <string>
#include <unordered_map>

using branch = bool;
namespace GraphElement {

std::string label(const std::string &label);

std::string box(const std::string &label);

std::string node(const std::string &question);

std::string result(const std::unordered_map<std::string, int> &data, branch b);

}

#endif //DEC_ISIONTREE_GRAPHELEMENTS_HPP
