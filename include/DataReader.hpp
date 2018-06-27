//
// Created by Julian on 13.06.18.
//

#ifndef TREE_CSVREADER_HPP
#define TREE_CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Dataset.hpp"
#include "Helper.hpp"

using std::move;
using std::vector;
using std::string;
using std::ifstream;
using boost::algorithm::split;
using Data = vector<vector<string>>;
using VecS = vector<string>;
/*
 * A class to read data from a csv file. Based on http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
 */

class DataReader
{
 private:
  string delimeter;

  bool hasEmptyStrings(const VecS& strings) const;
  bool isCommentLine(const string& line) const;

  Data training_data;
  Data testing_data;
  VecS labels;

 public:
  DataReader() = delete;
  DataReader(const Dataset& dataset, string delm = ",");

  inline Data& trainingData() { return training_data; }
  inline const Data& testingData() const { return testing_data; }
  inline const VecS& labels_() const { return labels; }
  /**
   * Parses through csv file line by line and
   * @return the data in vector of vector of strings
   */
  void processFile(const string& strings, Data& data);
};

#endif //TREE_CSVREADER_HPP
