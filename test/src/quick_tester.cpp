#include <decision_tree/decision_tree.hpp>

using namespace decision_tree;

int main() {
    DecisionTree dt(TrainingSet("../test/data/san_fran_vs_nyc.csv", SkipDescription::NO), TestingSet("../test/data/san_fran_vs_nyc_test.csv"));
    dt.test();
    dt.generateGraph("../graph.dot");
    return 0;
}
