/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *For more information, please refer to <http://unlicense.org>
*/
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
                continue;

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
