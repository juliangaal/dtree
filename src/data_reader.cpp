//
// Created by Julian on 13.06.18.
//
#include <thread>
#include <decision_tree/data_reader.hpp>

using namespace decision_tree;
using boost::algorithm::split;

DataReader::DataReader(const Dataset &dataset, std::string delim) :
        result_label{dataset.result_label},
        delimeter{std::move(delim)},
        training_data{},
        testing_data{},
        training_labels{},
        testing_labels{},
        missing_labels{false} {

    std::thread readTestingData([this, &dataset]() {
        return processFile(dataset.train.filename, training_data, training_labels);
    });

    std::thread readTrainingData([this, &dataset]() {
        return processFile(dataset.test.filename, testing_data, testing_labels);
    });

    readTrainingData.join();
    readTestingData.join();

    if (!result_label.empty())
        correctLabels();

    if (missing_labels)
        throw std::runtime_error("Check your labels: Are some missing? Training labels == testing labels?");

    if (training_data.empty())
        throw std::runtime_error("Can't open file: " + dataset.train.filename);

    if (testing_data.empty())
        throw std::runtime_error("Can't open file: " + dataset.test.filename);
}

void DataReader::processFile(const std::string &filename, Data &data, VecS &labels) {
    std::ifstream file(filename);
    if (!file)
        return;

    std::string line;
    int line_counter = 1;
    static constexpr int first_line = 1;

    while (getline(file, line)) {
        std::vector<std::string> vec;

        if (isCommentLine(line) || line.empty())
            continue;

        split(vec, line, boost::is_any_of(delimeter));
        if (line_counter == first_line) {
            if (hasEmptyStrings(vec)) {
                missing_labels = true;
                return;
            }

//            vec.pop_back();
            labels = std::move(vec);
        } else {
//            vec.pop_back();
            trimWhiteSpaces(vec);

            if (hasEmptyStrings(vec))
                correctMissingValues(data, vec);

            if (result_label.empty()) {
                data.emplace_back(std::move(vec));
            } else {
                swapResultData(vec, labels);
                data.emplace_back(std::move(vec));
            }
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

void DataReader::swapResultData(VecS &line, const VecS &labels) const {
    static const auto result = std::find(std::begin(labels), std::end(labels), result_label);
    if (result != std::end(labels)) {
        static const auto result_index = std::distance(std::begin(labels), result);
        std::iter_swap(std::begin(line) + result_index, std::end(line) - 1);
    }
}

void DataReader::correctLabels() {
    if (training_labels != testing_labels) {
        missing_labels = true;
        return;
    }

    const auto result = std::find(std::begin(training_labels), std::end(training_labels), result_label);
    if (result != std::end(training_labels))
        std::iter_swap(result, std::end(training_labels) - 1);
}

void DataReader::correctMissingValues(const Data &data, VecS &vec) const {
    const auto &last_line = data.back();
    vec.clear();
    // TODO: replace with stl::copy_if version
    std::copy(std::begin(last_line), std::end(last_line), std::back_inserter(vec));
}

void DataReader::trimWhiteSpaces(VecS &line) {
    for (auto &val: line)
        boost::trim(val);
}
