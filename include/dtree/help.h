/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *For more information, please refer to <http://unlicense.org>
*/

#ifndef DTREE_HELPER_HPP
#define DTREE_HELPER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>
#include <iterator>
#include <fmt/format.h>
#include <iostream>

namespace dtree {

using ClassCounter = std::unordered_map<std::string, int>;
using Data = std::vector<std::vector<std::string>>;
using VecS = std::vector<std::string>;

namespace help::print {

template<typename T>
void print_vector(const std::vector<T> &vec) {
    if (vec.empty())
        return;

    fmt::print("[ ");
    std::copy(begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, " "));
    fmt::print(" ]\n");
}

template<typename K, typename V>
void print_map(const std::unordered_map<K, V> &counter) {
    if (counter.empty())
        return;

    for (const auto& [key, val]: counter) {
        fmt::print("[{:>3}, {:0.1f}%", key, val);
        if (counter.size() > 1) fmt::print(" | ");
    }

    fmt::print(" ]\n");
}

} // namespace dtree::help::print

} // namespace dtree

#endif //DTREE_HELPER_HPP
