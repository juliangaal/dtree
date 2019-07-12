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

#include <dtree/question.h>
#include <dtree/help.h>

using namespace dtree;
using std::string;

Question::Question() : column_{}, value_{} {}

Question::Question(int column, string value) : column_{column}, value_{std::move(value)} {}

bool Question::match(const VecS &example) const {
    const string &val = example[column_];

    try {
        // faster than calling isNumeric on both!
        return std::stod(val) >= std::stod(value_);
    } catch (const std::exception &e) {
        return val == value_;
    }
}

string Question::toString(const VecS &labels) const {
    string condition = "==";
    if (isNumeric(value_))
        condition = ">=";
    return "Is " + labels[column_] + " " + condition + " " + value_ + "?";
}

const bool Question::isNumeric(const string &value) const {
    try {
        std::stod(value);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}
