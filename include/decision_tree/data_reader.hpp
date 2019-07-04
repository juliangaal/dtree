//
// Created by Julian on 13.06.18.
//

#ifndef TREE_CSVREADER_HPP
#define TREE_CSVREADER_HPP

#include <decision_tree/dataset.hpp>
#include <decision_tree/helpers.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

/*
 * A class to read data from a csv file. Based on http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
 */
namespace decision_tree {

class DataReader {
private:
    bool hasEmptyStrings(const decision_tree::VecS &strings) const;

    bool isCommentLine(const std::string &line) const;

    const std::string result_label;
    const std::string delimeter;
    decision_tree::Data training_data;
    decision_tree::Data testing_data;
    decision_tree::VecS training_labels;
    decision_tree::VecS testing_labels;
    bool missing_labels;

public:
    DataReader() = delete;

    DataReader(const Dataset &dataset, std::string delm = ",");

    inline const decision_tree::Data &trainingData() const { return training_data; }

    inline const decision_tree::Data &testingData() const { return testing_data; }

    inline const decision_tree::VecS &labels() const { return training_labels; }

    /**
     * Parses through csv file line by line and
     * @return the data in vector of vector of strings
     */
    void processFile(const std::string &strings, decision_tree::Data &data, decision_tree::VecS &labels);

    void swapResultData(decision_tree::VecS &line, const decision_tree::VecS &labels) const;

    void correctLabels();

    void trimWhiteSpaces(decision_tree::VecS &line);

    void correctMissingValues(const decision_tree::Data &data, decision_tree::VecS &vec) const;
};

} // namespace decision_tree

#endif //TREE_CSVREADER_HPP
