#include <sstream>
#include <algorithm>

#include <gumbo.h>

#include "../include/tools.h"

std::vector<std::string> SplitStr(const std::string &_str) {
    if (_str.empty()) {
        return {};
    }

    std::vector<std::string> tokens;
    std::istringstream string_stream(_str);
    std::string token;

    while (string_stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string RemoveWhspaces(const std::string &_str) {
    if (_str.empty()) {
        return {};
    }

    std::string res;
    res.reserve(_str.length() / 4 * 3);

    bool started = false;
    bool spacePending = false;

    for (const char c: _str) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (started) {
                spacePending = true;
            }
        } else {
            if (spacePending) {
                res += ' ';
                spacePending = false;
            }
            res += c;
            started = true;
        }
    }

    return res;
}

std::string EscapeHtml(const std::string_view &_str) {
    std::string res;
    res.reserve(_str.size() + _str.size() / 4);

    for (const char c: _str) {
        switch (c) {
            case '&':
                res += "&amp;";
                break;
            case '<':
                res += "&lt;";
                break;
            case '>':
                res += "&gt;";
                break;
            case '"':
                res += "&quot;";
                break;
            case '\'':
                res += "&#39;";
                break;
            default:
                res += c;
                break;
        }
    }

    return res;
}

std::string GetTagStr(const GumboStringPiece &_piece) {
    if (!_piece.data || _piece.length == 0) {
        return "";
    }
    return {_piece.data, _piece.length};
}

Tag ExtractTag(const std::vector<Tag> &_tags,
               GumboTag _tagName,
               const std::string &_attrName,
               const std::string &_attrValue) {
    if (_tags.empty()) {
        return Node(nullptr);
    }

    for (Tag _tag: _tags) {
        if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT) {
            continue;
        }
        if (_tag.GetNode()->v.element.tag != _tagName) {
            continue;
        }

        if (_attrName.empty()) {
            return _tag;
        }

        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());
        if (attr && attr->value && std::string(attr->value) == _attrValue) {
            return _tag;
        }
    }

    return Tag();
}

std::string MakeOneLine(const std::string &_input) {
    std::string result = _input;
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    return result;
}
