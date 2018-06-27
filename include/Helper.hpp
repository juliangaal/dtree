//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_HELPER_HPP
#define DEC__ISIONTREE_HELPER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <numeric>
#include <iterator>

using std::string;
using std::vector;
using std::unordered_map;
using Data = vector<vector<string>>;

namespace Helper::iterators {

struct RetrieveKey {
  template<typename T>
  typename T::first_type operator()(T keyValuePair) const {
    return keyValuePair.first;
  }
};

struct AddMapValue {
  template<typename S, typename T>
  int operator()(const S previous, const T map) const {
    return previous + map.second;
  }
};
}

namespace Helper::tree {

template <typename T>
int mapValueSum(unordered_map<T, int> counts) {
  return std::accumulate(counts.begin(), counts.end(), 0, iterators::AddMapValue());
}

//bool isNumeric(std::string value) {
//  double parsed_number = 0.0;
//
//  if (bool empty = value.empty(); !empty) {
//    try {
//      parsed_number = std::stod(value);
//      return true;
//    } catch (const std::exception &e) {
//      return false;
//    }
//  }
//  return false;
//}

}

namespace Helper::print {
template<typename T>
void print_vector(const vector<T> &vec) {
  if (vec.empty())
    return;

  std::cout << "{ ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<string>(std::cout, " "));
  std::cout << "}\n";
}

template<typename K, typename V>
void print_map(const unordered_map<K, V> &counter) {
  if (counter.empty())
    return;

  std::cout << "{ ";
  for (const auto& [key, val]: counter) {
    std::cout << key << ": " << val << " ";
  }
  std::cout << "}" << "\n";
}

}


#endif //DEC__ISIONTREE_HELPER_HPP
