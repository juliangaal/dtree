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
