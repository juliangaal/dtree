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
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // for std::optional<T>
#include <dtree/decision_tree.h>
#include <dtree/data_reader.h>

namespace py = pybind11;

PYBIND11_MODULE(dtree_py, m) {
    m.doc() = "pybind11 bindings for dtree";

    py::enum_<dtree::SkipDescription >(m, "SkipDescription", py::arithmetic())
        .value("YES", dtree::SkipDescription::YES)
        .value("NO", dtree::SkipDescription::NO)
        .export_values();

    py::class_<dtree::TrainingSet>(m, "TrainingSet")
            .def(py::init<std::string, dtree::SkipDescription, std::string>());

    py::class_<dtree::TestingSet>(m, "TestingSet")
            .def(py::init<std::string, std::string>());

    py::class_<dtree::DecisionTree>(m, "DecisionTree")
            .def(py::init<dtree::TrainingSet, dtree::TestingSet>())
            .def("build", &dtree::DecisionTree::build)
            .def("test", &dtree::DecisionTree::test)
            .def("generate_graph", &dtree::DecisionTree::generate_graph);
}


