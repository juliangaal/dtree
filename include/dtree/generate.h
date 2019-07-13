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

#ifndef DTREE_GRAPHGENERATOR_HPP
#define DTREE_GRAPHGENERATOR_HPP

#include <dtree/node.h>
#include <memory>
#include <filesystem>
#include <fstream>

namespace dtree::generate {

void init(const std::unique_ptr<Node> &root, const VecS &labels, const std::filesystem::path &filepath);

void traverse_generate(const std::unique_ptr<Node> &node, const VecS &labels, std::ofstream &file);

} // namespace dtree::generate

namespace dtree::graph_element {

std::string label(const std::string &label);

std::string box(const std::string &label, size_t hash);

std::string node(size_t hash);

std::string result(const std::unordered_map<std::string, int> &data, bool b);

} // namespace dtree::graph_element

#endif //DTREE_GRAPHGENERATOR_HPP
