#include <decision_tree/decision_tree.h>
#include <cassert>
#include <fmt/format.h>

using namespace decision_tree;

int main(int argc, char *argv[]) {
    auto trainfile = fmt::format("{}{}.csv", "../test/data/", argv[1]);
    auto testfile = fmt::format("{}{}_test.csv", "../test/data/", argv[1]);
    auto skipdesc = argc == 3 ? SkipDescription::YES : SkipDescription::NO;
    DecisionTree dt(TrainingSet(trainfile, skipdesc), TestingSet(testfile));
    dt.test();
    dt.generate_graph("../graph.dot");
    return 0;
}
