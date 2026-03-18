#ifndef TAG_HEADER
#define TAG_HEADER

#include <vector>
#include <string>

#include <curl/curl.h>

#include "node.h"
#include "utils.h"

#ifndef GUMBO_CLEAN
#define GUMBO_CLEAN(tag) \
  if (tag.GetOutput() != nullptr) { \
    gumbo_destroy_output(&kGumboDefaultOptions, tag.GetOutput()); \
  }
#endif

class Tag {
public:
    fn Tag();

    fn Tag(const Node &_node);

    fn Tag(const Tag &_tag);

    fn Tag(GumboNode *_node);

    void MakeRoot(const std::string &_htmlCode);

    auto
    fn operator=(const Node &_node) -> Tag &;

public:
    auto
    fn GetNode() const -> GumboNode *;

    GumboOutput *GetOutput();

    auto
    fn SetNode(GumboNode *_node) -> void;

    auto
    fn SetNode(Node _node) -> void;

public:
    auto
    fn GetText() const -> std::string;

    auto
    fn FindTag(GumboTag _tag,
               const std::string &_attrName,
               const std::string &_attrValue) const -> Tag;

    auto
    fn FindAllTags(GumboTag _tag,
                   const std::string &_attrName,
                   const std::string &_attrValue) -> std::vector<Tag>;

    auto
    fn FindTagAnyval(GumboTag _tag,
                     const std::string &_attrName,
                     const std::string &_attrValue) const -> Tag;

    auto
    fn FindTagAnysubval(GumboTag _tag,
                        const std::string &_attrName,
                        const std::string &_attrValue) const -> Tag;

    auto
    fn FindAllTagsAnyval(GumboTag _tag,
                         const std::string &_attrName,
                         const std::string &_attrValue) const -> std::vector<Tag>;

    auto
    fn FindAllTagsAnysubval(GumboTag _tag,
                            const std::string &_attrName,
                            const std::string &_attrValue) const -> std::vector<Tag>;

    auto
    fn GetHtmlView() -> std::string;

    Tag FindTagWithClassExc(GumboTag _targetTag, const std::string &_attrName,
                            const std::string &_attrValue,
                            const std::string &_excClass);

    Tag FindTagWithTagExc(GumboTag _targetTag, const std::string &_attrName,
                          const std::string &_attrValue,
                          const GumboTag &_excTag);

public:
    inline explicit
    fn operator bool() const {
        return tag.GetNode() != nullptr;
    }

private:
    Tag __FindTagWithClassExc(Tag &_tag, GumboTag _targetTag, const std::string &_attrName,
                              const std::string &_attrValue,
                              const std::string &_excClass);

    Tag __FindTagWithTagExc(Tag &_tag, GumboTag _targetTag, const std::string &_attrName,
                            const std::string &_attrValue,
                            const GumboTag &_excTag);

private:
    Node tag;
    GumboOutput *output;
};

#endif // TAG_HEADER
