//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DATASET_HPP
#define DECISIONTREE_DATASET_HPP

#include <string>

namespace decision_tree {

enum SkipDescription {
    YES,
    NO
};

struct TrainingSet {
    inline explicit TrainingSet(std::string filename, SkipDescription skipdesc, std::string delimiter = ",") : filename(
            std::move(filename)), skipdesc(skipdesc), delimiter(std::move(delimiter)) {}

    ~TrainingSet() = default;

    std::string filename;
    SkipDescription skipdesc;
    std::string delimiter;
};

struct TestingSet {
    inline explicit TestingSet(std::string filename, std::string delimiter = ",") : filename(
            std::move(filename)), delimiter(std::move(delimiter)) {}

    ~TestingSet() = default;

    std::string filename;
    std::string delimiter;
};

struct Train {
    std::string filename;
};

struct Test {
    std::string filename;
};

struct Dataset {
    Train train;
    Test test;
    std::string result_label;
};

} // namespace decision_tree

#endif //DECISIONTREE_DATASET_HPP
