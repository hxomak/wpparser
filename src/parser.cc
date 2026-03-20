#include <string>

#include "../include/parser.h"

#include <iostream>

#include "../include/Tag.h"
#include "../include/tools.h"
#include "../include/utils.h"

namespace {
    void __GetText(const Tag _tag, std::string &_res) {
        if (!_tag) {
            return;
        }
        if (_tag.GetNode()->type == GUMBO_NODE_TEXT || _tag.GetNode()->type == GUMBO_NODE_WHITESPACE) {
            _res += std::string(_tag.GetNode()->v.text.text);
            return;
        }
        if (_tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
            return;
        }
        const GumboVector *children = &_tag.GetNode()->v.element.children;
        for (size_t i = 0; i < children->length; ++i) {
            _res += " ";
            __GetText(static_cast<GumboNode *>(children->data[i]), _res);
        }
    }

    std::string __GetHtmlView(const GumboNode *node) {
        if (!node)
            return "";

        if (node->type == GUMBO_NODE_TEXT || node->type == GUMBO_NODE_WHITESPACE) {
            return GetTagStr(node->v.text.original_text);
        }

        if (node->type != GUMBO_NODE_ELEMENT)
            return "";

        const char *tag_name = gumbo_normalized_tagname(node->v.element.tag);
        std::string result = "<" + std::string(tag_name) + ">";

        const GumboVector *children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            result += __GetHtmlView(static_cast<const GumboNode *>(children->data[i]));
        }

        static const GumboTag void_tags[] = {
            GUMBO_TAG_AREA, GUMBO_TAG_BASE, GUMBO_TAG_BR, GUMBO_TAG_COL,
            GUMBO_TAG_EMBED, GUMBO_TAG_HR, GUMBO_TAG_IMG, GUMBO_TAG_INPUT,
            GUMBO_TAG_LINK, GUMBO_TAG_META, GUMBO_TAG_PARAM, GUMBO_TAG_SOURCE,
            GUMBO_TAG_TRACK, GUMBO_TAG_WBR
        };

        bool is_void = false;
        for (size_t j = 0; j < sizeof(void_tags) / sizeof(GumboTag); ++j) {
            if (node->v.element.tag == void_tags[j]) {
                is_void = true;
                break;
            }
        }

        if (!is_void) {
            result += "</" + std::string(tag_name) + ">";
        }

        return result;
    }
} // namespace

std::string GetText(const Tag _tag) {
    std::string res{};
    __GetText(_tag, res);
    return RemoveWhspaces(res);
}

Tag FindTag(const Tag _tag,
            GumboTag _tagName,
            const std::string &_attrName,
            const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return nullptr;
    }
    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            return _tag;
        }
        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());
        if (attr && std::string(attr->value) == _attrValue) {
            return _tag;
        }
    }
    GumboVector *children = &_tag.GetNode()->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        Tag foundNode = FindTag(static_cast<GumboNode *>(children->data[i]), _tagName, _attrName, _attrValue);
        if (foundNode) {
            return foundNode;
        }
    }
    return Tag(nullptr);
}

std::vector<Tag> FindAllTags(const Tag _tag,
                             GumboTag _tagName,
                             const std::string &_attrName,
                             const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return {};
    }

    std::vector<Tag> results;

    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            results.push_back(_tag);
        } else {
            GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());

            if (attr && std::string(attr->value) == _attrValue) {
                results.push_back(_tag);
            }
        }
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i) {
        std::vector<Tag> child_results = FindAllTags(static_cast<GumboNode *>(children->data[i]), _tagName,
                                                      _attrName, _attrValue);
        results += child_results;
    }

    return results;
}

Tag FindTagAnyval(const Tag _tag,
                  GumboTag _tagName,
                  const std::string &_attrName,
                  const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return nullptr;
    }

    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            return _tag;
        }

        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());

        if (attr) {
            std::vector<std::string> values = SplitStr(attr->value);
            for (const auto &val: values) {
                if (val == _attrValue) {
                    return _tag;
                }
            }
        }
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i) {
        Tag found = FindTagAnyval(static_cast<GumboNode *>(children->data[i]), _tagName, _attrName, _attrValue);

        if (found) {
            return found;
        }
    }

    return Tag();
}

Tag FindTagAnysubval(const Tag _tag,
                     GumboTag _tagName,
                     const std::string &_attrName,
                     const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return nullptr;
    }

    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            return _tag;
        }

        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());

        if (attr && std::string(attr->value).find(_attrValue) != std::string::npos) {
            return _tag;
        }
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i) {
        Tag found = FindTagAnysubval(static_cast<GumboNode *>(children->data[i]), _tagName, _attrName,
                                      _attrValue);

        if (found) {
            return found;
        }
    }

    return Tag();
}

std::vector<Tag> FindAllTagsAnyval(const Tag _tag,
                                   GumboTag _tagName,
                                   const std::string &_attrName,
                                   const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return {};
    }

    std::vector<Tag> results;

    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            results.push_back(_tag);
        } else {
            GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());

            if (attr) {
                std::vector<std::string> values = SplitStr(attr->value);
                for (const auto &val: values) {
                    if (val == _attrValue) {
                        results.push_back(_tag);
                        break;
                    }
                }
            }
        }
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i) {
        std::vector<Tag> childResults = FindAllTagsAnyval(static_cast<GumboNode *>(children->data[i]),
                                                          _tagName, _attrName, _attrValue);
        results += childResults;
    }

    return results;
}

std::vector<Tag> FindAllTagsAnysubval(const Tag _tag,
                                      GumboTag _tagName,
                                      const std::string &_attrName,
                                      const std::string &_attrValue) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
        return {};
    }

    std::vector<Tag> results;

    if (_tag.GetNode()->v.element.tag == _tagName) {
        if (_attrName.empty()) {
            results.push_back(_tag);
        } else {
            GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());

            if (attr && std::string(attr->value).find(_attrValue) != std::string::npos) {
                results.push_back(_tag);
            }
        }
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i) {
        std::vector<Tag> childResults = FindAllTagsAnysubval(
            static_cast<GumboNode *>(children->data[i]), _tagName, _attrName, _attrValue);
        results += childResults;
    }

    return results;
}

std::string GetHtmlView(const Tag &_tag) {
    return __GetHtmlView(_tag.GetNode());
}
