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

#ifndef DTREE_DATASET_H
#define DTREE_DATASET_H

#include <string>
#include <filesystem>

namespace dtree {

enum SkipDescription {
    YES,
    NO
};

struct TrainingSet {
    inline explicit TrainingSet(std::string file, SkipDescription skipdesc, std::string delimiter = ",") : file_{
            std::move(file)}, skipdesc_{skipdesc}, delimiter_{std::move(delimiter)} {}

    ~TrainingSet() = default;

    std::filesystem::path file_;
    SkipDescription skipdesc_;
    std::string delimiter_;
};

struct TestingSet {
    inline explicit TestingSet(std::string file, std::string delimiter = ",") : file_{
            std::move(file)}, delimiter_{std::move(delimiter)} {}

    ~TestingSet() = default;

    std::filesystem::path file_;
    std::string delimiter_;
};

} // namespace dtree

#endif //DTREE_DATASET_H