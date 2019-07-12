//
// Created by Julian on 13.06.18.
//
#include <thread>
#include <filesystem>
#include <dtree/data_reader.h>

using namespace dtree;
using boost::algorithm::split;
namespace fs = std::filesystem;

DataReader::DataReader(const TrainingSet &trainset, const TestingSet &testset) :
        training_data_{},
        testing_data_{},
        training_labels_{},
        testing_labels_{} {

    if (!fs::exists(trainset.file_))
        throw std::runtime_error(fmt::format("{} doesn't exist", trainset.file_.string()));

    if (fs::is_directory(trainset.file_))
        throw std::runtime_error(fmt::format("{} is a directory. Need .csv file", trainset.file_.string()));

    if (!fs::exists(testset.file_))
        throw std::runtime_error(fmt::format("{} doesn't exist", testset.file_.string()));

    if (fs::is_directory(testset.file_))
        throw std::runtime_error(fmt::format("{} is a directory. Need .csv file", testset.file_.string()));

    std::thread readTrainingData([this, &trainset]() {
        return process_file(trainset.file_, training_data_, training_labels_, trainset.skipdesc_, trainset.delimiter_);
    });

    std::thread readTestingData([this, &testset]() {
        return process_file(testset.file_, testing_data_, testing_labels_, SkipDescription::NO, testset.delimiter_);
    });

    readTrainingData.join();
    readTestingData.join();
}

void DataReader::process_file(const std::filesystem::path &filepath, Data &data, VecS &labels, SkipDescription skipdesc,
                              const std::string &delimiter) {
    std::ifstream file(filepath);

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
            if (has_empty_strings(vec))
                throw std::runtime_error("Check your labels: Are some missing? Training labels == testing labels?");

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
