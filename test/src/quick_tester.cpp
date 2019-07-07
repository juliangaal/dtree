#include <decision_tree/decision_tree.hpp>

using namespace decision_tree;

int main() {
    DecisionTree dt(TrainingSet("../test/data/mpg.csv", SkipDescription::YES), TestingSet("../test/data/mpg_test.csv"));
    dt.test();
    dt.generateGraph("../graph.dot");
    return 0;
}
