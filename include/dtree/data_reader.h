//
// Created by Julian on 13.06.18.
//

#ifndef TREE_CSVREADER_HPP
#define TREE_CSVREADER_HPP

#include <dtree/dataset.h>
#include <dtree/help.h>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

/*
 * A class to read data from a csv file. Based on http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
 */
namespace dtree {

class DataReader {
private:
    [[nodiscard]]
    bool has_empty_strings(const dtree::VecS &strings) const;
    [[nodiscard]]
    bool is_comment_line(const std::string &line) const;

    dtree::Data training_data_;
    dtree::Data testing_data_;
    dtree::VecS training_labels_;
    dtree::VecS testing_labels_;

public:
    DataReader() = delete;

    DataReader(const TrainingSet &trainset, const TestingSet &testset);

    [[nodiscard]]
    inline const dtree::Data &training_data() const { return training_data_; }
    [[nodiscard]]
    inline const dtree::Data &testing_data() const { return testing_data_; }
    [[nodiscard]]
    inline const dtree::VecS &labels() const { return training_labels_; }

    /**
     * Parses through csv file line by line and
     * @return the data in vector of vector of strings
     */
    void process_file(const std::filesystem::path &filepath, Data &data, VecS &labels, SkipDescription skipdesc,
                      const std::string &delimiter);

    void time_white_spaces(dtree::VecS &line);

    void correct_missing_values(const dtree::Data &data, dtree::VecS &vec) const;
};

} // namespace dtree

#endif //TREE_CSVREADER_HPP
