//
// Created by Julian on 13.06.18.
//

#ifndef TREE_CSVREADER_HPP
#define TREE_CSVREADER_HPP

#include <decision_tree/dataset.h>
#include <decision_tree/help.h>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

/*
 * A class to read data from a csv file. Based on http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
 */
namespace decision_tree {

class DataReader {
private:
    bool has_empty_strings(const decision_tree::VecS &strings) const;

    bool is_comment_line(const std::string &line) const;

    decision_tree::Data training_data_;
    decision_tree::Data testing_data_;
    decision_tree::VecS training_labels_;
    decision_tree::VecS testing_labels_;
    bool missing_labels;

public:
    DataReader() = delete;

    DataReader(const TrainingSet &trainset, const TestingSet &testset);

    inline const decision_tree::Data &training_data() const { return training_data_; }

    inline const decision_tree::Data &testing_data() const { return testing_data_; }

    inline const decision_tree::VecS &labels() const { return training_labels_; }

    /**
     * Parses through csv file line by line and
     * @return the data in vector of vector of strings
     */
    void process_file(const std::string &filename, Data &data, VecS &labels, SkipDescription skipdesc,
                      std::string delimiter);

    void time_white_spaces(decision_tree::VecS &line);

    void correct_missing_values(const decision_tree::Data &data, decision_tree::VecS &vec) const;
};

} // namespace decision_tree

#endif //TREE_CSVREADER_HPP
