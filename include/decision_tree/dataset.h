//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DATASET_H
#define DECISIONTREE_DATASET_H

#include <string>
#include <filesystem>

namespace decision_tree {

enum SkipDescription {
    YES,
    NO
};

struct TrainingSet {
    inline explicit TrainingSet(std::string file, SkipDescription skipdesc, std::string delimiter = ",") : file_{
            std::move(file)}, skipdesc_{skipdesc}, delimiter_{std::move(delimiter)} {}

    ~TrainingSet() = default;

    std::filesystem::path file_;
    SkipDescription skipdesc_;
    std::string delimiter_;
};

struct TestingSet {
    inline explicit TestingSet(std::string file, std::string delimiter = ",") : file_{
            std::move(file)}, delimiter_{std::move(delimiter)} {}

    ~TestingSet() = default;

    std::filesystem::path file_;
    std::string delimiter_;
};

} // namespace decision_tree

#endif //DECISIONTREE_DATASET_H
