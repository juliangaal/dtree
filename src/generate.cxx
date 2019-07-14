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
#include <dtree/generate.h>
#include <dtree/help.h>
#include <algorithm>
#include <fmt/format.h>

using namespace dtree;
namespace elem = dtree::graph_element;
namespace fs = std::filesystem;

using std::string;

void generate::init(const std::unique_ptr<Node> &root, const VecS &labels, const std::filesystem::path &filepath) {
    if (fs::is_directory(filepath))
        throw std::runtime_error(fmt::format("Can't generate graph at {}\n", filepath.string()));

    std::ofstream myfile;
    myfile.open(filepath);

    myfile << "digraph {\n";
    traverse_generate(root, labels, myfile);
    myfile << "}";
    myfile.close();
}

void generate::traverse_generate(const std::unique_ptr<Node> &node, const VecS &labels, std::ofstream &file) {
    static const string spacing = "   ";
    static const string connector = " -> ";
    if (!node)
        return;

    if (node->predicts())
        return;

    const auto question = node->question().value().toString(labels);
    const auto hash = node->hash(labels);

    file << spacing << elem::box(question, hash);
    file << spacing << elem::node(hash) << connector;

    if (node->true_branch()->predicts()) {
        file << elem::result(node->true_branch()->predictions().value(), true);
    } else {
        file << elem::node(node->true_branch()->hash(labels)) << elem::label("True");
    }

    file << spacing << elem::node(hash) << connector;

    if (node->false_branch()->predicts()) {
        file << elem::result(node->false_branch()->predictions().value(), false);
    } else {
        file << elem::node(node->false_branch()->hash(labels)) << elem::label("False");
    }

    traverse_generate(node->true_branch(), labels, file);
    traverse_generate(node->false_branch(), labels, file);
}

string graph_element::label(const string &label) {
    return " [label=\"" + label + "\"];\n";
}

string graph_element::node(size_t hash) {
    return fmt::format("\"{}\"", hash);
}

string graph_element::box(const string &label, size_t hash) {
    return fmt::format("\"{}\" [label=\"{}\", shape=box];\n", hash, label);
}

string graph_element::result(const std::unordered_map<string, int> &data, bool branch) {
    static int id = 0;
    string result = "\"";
    double sum = std::accumulate(data.begin(), data.end(), 0, [](auto curr, const auto& entry) { return curr + entry.second; });
    size_t map_size = data.size();
    size_t counter = 1;

    string classification{};
    for (const auto& [k, v]: data) {
        classification += fmt::format("{}: {:0.1f}%", k , v / sum * 100);
        if (counter++ < map_size)
            classification += "\\n ";
    }
    result += classification;

    string values = "\\nvalues: ";
    for (const auto& [k, v]: data) {
        values += fmt::format("{} ", v);
    }

    result += values;

    string result_id = fmt::format("\\nid: {}", id++);
    result += result_id;

    string result_box = fmt::format("   {}\" {};\n", result, "[shape=box]");
    string label = fmt::format("\" {}", branch ? graph_element::label("True") : graph_element::label("False"));
    result += label;

    result += result_box;
    return result;
}
