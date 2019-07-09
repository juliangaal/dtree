//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DATASET_H
#define DECISIONTREE_DATASET_H

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

} // namespace decision_tree

#endif //DECISIONTREE_DATASET_H
