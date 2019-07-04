#include <decision_tree/decision_tree.hpp>

using namespace decision_tree;

int main() {
    Dataset d{};
    d.train.filename = "../test/data/san_fran_vs_nyc.csv";
    d.test.filename = "../test/data/san_fran_vs_nyc_test.csv";

    DecisionTree dt(d);
    dt.test();
    dt.generateGraph("../graph.dot");
    return 0;
}
