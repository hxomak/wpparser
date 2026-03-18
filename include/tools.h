#ifndef TOOLS_HEADER
#define TOOLS_HEADER

#include <string>
#include <vector>

#include "utils.h"
#include "Tag.h"

template<typename T>
auto
fn operator+=(std::vector<T> &_lv, const std::vector<T> &_rv) -> std::vector<T> & {
    _lv.insert(_lv.end(), _rv.begin(), _rv.end());
    return _lv;
}

/**
 * @brief Splits string into vector of space-separated
 * words.
 *
 * @param _str text to split into words
 * @return Vector of split words
 */
auto
fn SplitStr(const std::string &_str) -> std::vector<std::string>;

/**
 * @brief Replaces all repeated spaces and whitespaces like t, r, n
 * with one space. Removes all unnecessary spaces.
 *
 * @param _str text to edit
 * @return Text without unnecessary white spaces
 */
auto
fn RemoveWhspaces(const std::string &_str) -> std::string;

/**
 * @brief Replaces special symbols
 * with their safe variants for html-sites.
 *
 * @param _str text to edit
 * @return Text with replaces special symbols
 */
auto
fn EscapeHtml(const std::string_view &_str) -> std::string;

auto
fn GetTagStr(const GumboStringPiece &_piece) -> std::string;

/**
 * @brief Finds first tag whose attribute values
 * equal to attr_value in vector of nodes.
 * If no attribute name is given than finds the first tag with
 * the same tag.
 *
 * @param nodes vector of nodes to find tag from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value which must be a substring in values
 * @return The first found tag with attribute value that
 * equals to attr_value
 */
auto
fn ExtractTag(const std::vector<Tag> &_tags,
              GumboTag _tagName,
              const std::string &_attrName,
              const std::string &_attrValue) -> Tag;

std::string MakeOneLine(const std::string &_input);

#endif // TOOLS_HEADER
