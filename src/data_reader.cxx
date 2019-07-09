//
// Created by Julian on 13.06.18.
//
#include <thread>
#include <decision_tree/data_reader.h>

using namespace decision_tree;
using boost::algorithm::split;

DataReader::DataReader(const TrainingSet &trainset, const TestingSet &testset) :
        training_data_{},
        testing_data_{},
        training_labels_{},
        testing_labels_{},
        missing_labels{false} {

    std::thread readTrainingData([this, &trainset]() {
        return process_file(trainset.filename, training_data_, training_labels_, trainset.skipdesc, trainset.delimiter);
    });

    std::thread readTestingData([this, &testset]() {
        return process_file(testset.filename, testing_data_, testing_labels_, SkipDescription::NO, testset.delimiter);
    });

    readTrainingData.join();
    readTestingData.join();

    if (missing_labels)
        throw std::runtime_error("Check your labels: Are some missing? Training labels == testing labels?");

    if (training_data_.empty())
        throw std::runtime_error("Can't open file: " + trainset.filename);

    if (testing_data_.empty())
        throw std::runtime_error("Can't open file: " + testset.filename);
}

void DataReader::process_file(const std::string &filename, Data &data, VecS &labels, SkipDescription skipdesc,
                              std::string delimiter) {
    std::ifstream file(filename);
    if (!file)
        return;

    std::string line;
    int line_counter = 1;
    static constexpr int first_line = 1;

    while (getline(file, line)) {
        std::vector<std::string> vec(labels.size());

        if (is_comment_line(line) || line.empty())
            continue;

        split(vec, line, boost::is_any_of(delimiter));

        if (skipdesc == SkipDescription::YES) vec.pop_back();

        if (line_counter == first_line) {
            if (has_empty_strings(vec)) {
                missing_labels = true;
                return;
            }

            labels = std::move(vec);
        } else {
            time_white_spaces(vec);

            if (has_empty_strings(vec))
                correct_missing_values(data, vec);

            data.emplace_back(std::move(vec));
        }
        ++line_counter;
    }
    file.close();
}

bool DataReader::has_empty_strings(const std::vector<std::string> &strings) const {
    return std::any_of(std::begin(strings), std::end(strings), [](const auto &v) { return v.empty(); });
}

bool DataReader::is_comment_line(const std::string &line) const {
    return line.find('#') != std::string::npos;
}

void DataReader::correct_missing_values(const Data &data, VecS &vec) const {
    const auto &last_line = data.back();
    vec.clear();
    // TODO: replace with stl::copy_if version
    std::copy(std::begin(last_line), std::end(last_line), std::back_inserter(vec));
}

void DataReader::time_white_spaces(VecS &line) {
    for (auto &val: line) boost::trim(val);
}
