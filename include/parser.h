#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <vector>
#include <string>

#include <gumbo.h>

#include "Tag.h"
#include "utils.h"

/**
 * @brief Extracts all text from tag including inner tags
 * with spaces adding between different tags
 *
 * @param node tag to extract text from
 * @return All text with spaces between them from the
 * tag and inner tags
 */
std::string GetText(const Tag _tag);

/**
 * @brief Finds first tag with this attribute in this node.
 * If no attribute name is given than finds the first tag with
 * the same tag.
 *
 * @param node node to find tag from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value to search for
 * @return The first found tag with the same tag attribute name and value
 */
Tag FindTag(const Tag _tag,
            GumboTag _tagName,
            const std::string &_attrName,
            const std::string &_attrValue);

/**
 * @brief Finds all tags with this attribute in this node.
 * If no attribute name is given than finds the all tags with
 * the same tag.
 *
 * @param node node to find tag from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value to search for
 * @return The all found tags with the same tag attribute name and value
 */
std::vector<Tag> FindAllTags(const Tag _tag,
                               GumboTag _tagName,
                               const std::string &_attrName,
                               const std::string &_attrValue);

/**
 * @brief Finds first tag whose attribute values include attr_value in this node.
 * If no attribute name is given than finds the first tag with
 * the same tag.
 *
 * @param node node to find tag from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value which must be included in values
 * @return The first found tag with attribute values that
 * include attr_value
 */
Tag FindTagAnyval(const Tag _tag,
                  GumboTag _tagName,
                  const std::string &_attrName,
                  const std::string &_attrValue);

/**
 * @brief Finds first tag whose attribute values has substring attr_value in this node.
 * If no attribute name is given than finds the first tag with
 * the same tag.
 *
 * @param node node to find tag from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value which must be a substring in values
 * @return The first found tag with attribute value that has
 * substring of attr_value
 */
Tag FindTagAnysubval(const Tag _tag,
                    GumboTag _tagName,
                    const std::string &_attrName,
                    const std::string &_attrValue);

/**
 * @brief Finds all tags whose attribute values include attr_value in this node.
 * If no attribute name is given than finds all tags with the same tag.
 *
 * @param node node to find tags from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value which must be included in values
 * @return The all found tags with attribute values that include attr_value
 */
std::vector<Tag> FindAllTagsAnyval(const Tag _tag,
                                   GumboTag _tagName,
                                   const std::string &_attrName,
                                   const std::string &_attrValue);

/**
 * @brief Finds all tags whose attribute values has substring attr_value in this node.
 * If no attribute name is given than finds all tags with the same tag.
 *
 * @param node node to find tags from
 * @param tag tag name to search for
 * @param attr_name attribute name to search for
 * @param attr_value attribute value which must be a substring in values
 * @return The all found tags with attribute value that has substring of attr_value
 */
std::vector<Tag> FindAllTagsAnysubval(const Tag _tag,
                                       GumboTag _tagName,
                                       const std::string &_attrName,
                                       const std::string &_attrValue);


std::string GetHtmlView(const Tag &_tag);

#endif // PARSER_HEADER
