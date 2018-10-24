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

using Data = std::vector<std::vector<std::string>>;

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
int mapValueSum(std::unordered_map<T, int> counts) {
  return std::accumulate(begin(counts), std::end(counts), 0, iterators::AddMapValue());
}
}

namespace Helper::print {
template<typename T>
void print_vector(const std::vector<T> &vec) {
  if (vec.empty())
    return;

  std::cout << "{ ";
  std::copy(begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, " "));
  std::cout << "}\n";
}

template<typename K, typename V>
void print_map(const std::unordered_map<K, V> &counter) {
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
