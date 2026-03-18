#include "../include/Tag.h"
#include "../include/node.h"
#include "../include/parser.h"

fn Tag::Tag()
    : tag(), output() {}

fn Tag::Tag(const Node &_node)
    : tag(_node.GetNode()), output() {}

fn Tag::Tag(const Tag &_tag)
    : tag(_tag.tag.GetNode()), output() {}

fn Tag::Tag(GumboNode *_node)
    : tag(_node), output() {}

void Tag::MakeRoot(const std::string &_htmlCode) {
    this->output = gumbo_parse(_htmlCode.c_str());
    this->tag = this->output->root;
}

auto
fn Tag::operator=(const Node &_node) -> Tag & {
    this->tag.SetNode(_node.GetNode());
    return *this;
}

auto
fn Tag::GetNode() const -> GumboNode * {
    return this->tag.GetNode();
}

GumboOutput *Tag::GetOutput() {
    return this->output;
}

auto
fn Tag::SetNode(GumboNode *_node) -> void {
    this->tag.SetNode(_node);
}

auto
fn Tag::SetNode(Node _node) -> void {
    this->tag.SetNode(_node.GetNode());
}

auto
fn Tag::GetText() const -> std::string {
    return ::GetText(this->tag);
}

auto
fn Tag::FindTag(GumboTag _tag,
                const std::string &_attrName,
                const std::string &_attrValue) const -> Tag {
    return ::FindTag(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::FindAllTags(GumboTag _tag,
                    const std::string &_attrName,
                    const std::string &_attrValue) -> std::vector<Tag> {
    return ::FindAllTags(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::FindTagAnyval(GumboTag _tag,
                      const std::string &_attrName,
                      const std::string &_attrValue) const -> Tag {
    return ::FindTagAnyval(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::FindTagAnysubval(GumboTag _tag,
                         const std::string &_attrName,
                         const std::string &_attrValue) const -> Tag {
    return ::FindTagAnysubval(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::FindAllTagsAnyval(GumboTag _tag,
                          const std::string &_attrName,
                          const std::string &_attrValue) const -> std::vector<Tag> {
    return ::FindAllTagsAnyval(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::FindAllTagsAnysubval(GumboTag _tag,
                             const std::string &_attrName,
                             const std::string &_attrValue) const -> std::vector<Tag> {
    return ::FindAllTagsAnysubval(this->tag, _tag, _attrName, _attrValue);
}

auto
fn Tag::GetHtmlView() -> std::string {
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
