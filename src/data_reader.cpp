//
// Created by Julian on 13.06.18.
//
#include <thread>
#include <decision_tree/data_reader.hpp>

using namespace decision_tree;
using boost::algorithm::split;

DataReader::DataReader(const TrainingSet &trainset, const TestingSet &testset) :
        training_data{},
        testing_data{},
        training_labels{},
        testing_labels{},
        missing_labels{false} {

    std::thread readTrainingData([this, &trainset]() {
        return processFile(trainset.filename, training_data, training_labels, trainset.skipdesc, trainset.delimiter);
    });

    std::thread readTestingData([this, &testset]() {
        return processFile(testset.filename, testing_data, testing_labels, SkipDescription::NO, testset.delimiter);
    });

    readTrainingData.join();
    readTestingData.join();

    if (missing_labels)
        throw std::runtime_error("Check your labels: Are some missing? Training labels == testing labels?");

    if (training_data.empty())
        throw std::runtime_error("Can't open file: " + trainset.filename);

    if (testing_data.empty())
        throw std::runtime_error("Can't open file: " + testset.filename);
}

void DataReader::processFile(const std::string &filename, Data &data, VecS &labels, SkipDescription skipdesc,
                             std::string delimiter) {
    std::ifstream file(filename);
    if (!file)
        return;

    std::string line;
    int line_counter = 1;
    static constexpr int first_line = 1;

    while (getline(file, line)) {
        std::vector<std::string> vec(labels.size());

        if (isCommentLine(line) || line.empty())
            continue;

        split(vec, line, boost::is_any_of(delimiter));

//        if (skipdesc == SkipDescription::YES) vec.pop_back();

        if (line_counter == first_line) {
            if (hasEmptyStrings(vec)) {
                missing_labels = true;
                return;
            }

            labels = std::move(vec);
        } else {
            trimWhiteSpaces(vec);

            if (hasEmptyStrings(vec))
                correctMissingValues(data, vec);

            data.emplace_back(std::move(vec));
        }
        ++line_counter;
    }
    file.close();
}

bool DataReader::hasEmptyStrings(const std::vector<std::string> &strings) const {
    return std::any_of(std::begin(strings), std::end(strings), [](const auto &v) { return v.empty(); });
}

bool DataReader::isCommentLine(const std::string &line) const {
    return line.find('#') != std::string::npos;
}

void DataReader::correctMissingValues(const Data &data, VecS &vec) const {
    const auto &last_line = data.back();
    vec.clear();
    // TODO: replace with stl::copy_if version
    std::copy(std::begin(last_line), std::end(last_line), std::back_inserter(vec));
}

void DataReader::trimWhiteSpaces(VecS &line) {
    for (auto &val: line) boost::trim(val);
}
