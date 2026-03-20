#include "../include/Tag.h"
#include "../include/node.h"
#include "../include/parser.h"

Tag::Tag()
    : tag(), output() {}

Tag::Tag(const Node &_node)
    : tag(_node.GetNode()), output() {}

Tag::Tag(const Tag &_tag)
    : tag(_tag.tag.GetNode()), output() {}

Tag::Tag(GumboNode *_node)
    : tag(_node), output() {}

void Tag::MakeRoot(const std::string &_htmlCode) {
    this->output = gumbo_parse(_htmlCode.c_str());
    this->tag = this->output->root;
}

Tag &Tag::operator=(const Node &_node) {
    this->tag.SetNode(_node.GetNode());
    return *this;
}

GumboNode *Tag::GetNode() const {
    return this->tag.GetNode();
}

GumboOutput *Tag::GetOutput() {
    return this->output;
}

void Tag::SetNode(GumboNode *_node) {
    this->tag.SetNode(_node);
}

void Tag::SetNode(Node _node) {
    this->tag.SetNode(_node.GetNode());
}

std::string Tag::GetText() const {
    return ::GetText(this->tag);
}

Tag Tag::FindTag(GumboTag _tag,
                const std::string &_attrName,
                const std::string &_attrValue) const {
    return ::FindTag(this->tag, _tag, _attrName, _attrValue);
}

std::vector<Tag> Tag::FindAllTags(GumboTag _tag,
                                    const std::string &_attrName,
                                    const std::string &_attrValue) {
    return ::FindAllTags(this->tag, _tag, _attrName, _attrValue);
}

Tag Tag::FindTagAnyval(GumboTag _tag,
                      const std::string &_attrName,
                      const std::string &_attrValue) const {
    return ::FindTagAnyval(this->tag, _tag, _attrName, _attrValue);
}

Tag Tag::FindTagAnysubval(GumboTag _tag,
                          const std::string &_attrName,
                          const std::string &_attrValue) const {
    return ::FindTagAnysubval(this->tag, _tag, _attrName, _attrValue);
}

std::vector<Tag> Tag::FindAllTagsAnyval(GumboTag _tag,
                                          const std::string &_attrName,
                                          const std::string &_attrValue) const {
    return ::FindAllTagsAnyval(this->tag, _tag, _attrName, _attrValue);
}

std::vector<Tag> Tag::FindAllTagsAnysubval(GumboTag _tag,
                                              const std::string &_attrName,
                                              const std::string &_attrValue) const {
    return ::FindAllTagsAnysubval(this->tag, _tag, _attrName, _attrValue);
}

std::string Tag::GetHtmlView() {
    return ::GetHtmlView(*this);
}

Tag Tag::__FindTagWithClassExc(Tag &_tag, GumboTag _targetTag, const std::string &_attrName,
                                const std::string &_attrValue,
                                const std::string &_excClass) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT)
        return {};

    if (!_excClass.empty() && _tag.GetNode()->v.element.tag == GUMBO_TAG_DIV) {
        GumboAttribute *class_attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, "class");
        if (class_attr && std::string(class_attr->value) == _excClass) {
            return {};
        }
    }

    if (_tag.GetNode()->v.element.tag == _targetTag) {
        if (_excClass.empty())
            return _tag;
        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());
        if (attr && std::string(attr->value) == _attrValue)
            return _tag;
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        Tag iTag{static_cast<GumboNode *>(children->data[i])};
        auto found = __FindTagWithClassExc(iTag, _targetTag, _attrName, _attrValue, _excClass);
        if (found) {
            return found;
        }
    }
    return {};
}

Tag Tag::__FindTagWithTagExc(Tag &_tag, GumboTag _targetTag, const std::string &_attrName,
                              const std::string &_attrValue,
                              const GumboTag &_excTag) {
    if (!_tag || _tag.GetNode()->type != GUMBO_NODE_ELEMENT)
        return {};

    if (_tag.GetNode()->v.element.tag == _excTag) {
        return {};
    }

    if (_tag.GetNode()->v.element.tag == _targetTag) {
        if (_attrValue.empty())
            return _tag;
        GumboAttribute *attr = gumbo_get_attribute(&_tag.GetNode()->v.element.attributes, _attrName.c_str());
        if (attr && std::string(attr->value) == _attrValue)
            return _tag;
    }

    GumboVector *children = &_tag.GetNode()->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        Tag iTag{static_cast<GumboNode *>(children->data[i])};
        auto found = __FindTagWithTagExc(iTag, _targetTag, _attrName, _attrValue, _excTag);
        if (found) {
            return found;
        }
    }
    return {};
}

Tag Tag::FindTagWithClassExc(GumboTag _targetTag, const std::string &_attrName,
                              const std::string &_attrValue,
                              const std::string &_excClass) {
    return __FindTagWithClassExc(*this, _targetTag, _attrName, _attrValue, _excClass);
}

Tag Tag::FindTagWithTagExc(GumboTag _targetTag, const std::string &_attrName,
                            const std::string &_attrValue,
                            const GumboTag &_excTag) {
    return __FindTagWithTagExc(*this, _targetTag, _attrName, _attrValue, _excTag);
}
