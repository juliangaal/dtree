#include <decision_tree/decision_tree.hpp>
#include <cassert>
#include <fmt/format.h>

using namespace decision_tree;

int main(int argc, char *argv[]) {
    assert(argc == 3);

    auto trainfile = fmt::format("{}{}.csv", "../test/data/", argv[1]);
    auto testfile = fmt::format("{}{}_test.csv", "../test/data/", argv[1]);
    auto skipdesc = argv[2] == 0 ? SkipDescription::NO : SkipDescription::YES;
    DecisionTree dt(TrainingSet(trainfile, skipdesc), TestingSet(testfile));
    dt.test();
    dt.generateGraph("../graph.dot");
    return 0;
}
