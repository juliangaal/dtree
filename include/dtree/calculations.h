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

#ifndef DTREE_CALCULATIONS_H
#define DTREE_CALCULATIONS_H

#include <dtree/question.h>
#include <dtree/help.h>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_map>

namespace dtree::calculations {

std::tuple <Data, Data> partition(const Data &data, const Question &q);

float gini(const Data &data);

float info_gain(const Data &true_rows, const Data &false_rows, float current_uncertainty);

std::tuple<double, Question> find_best_split(const Data &rows);

VecS unique_values(const dtree::Data &data, size_t column);

ClassCounter class_counts(const Data &data);

} // namespace Calculations

#endif //DTREE_CALCULATIONS_H
