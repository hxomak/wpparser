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
    Tag();

    Tag(const Node &_node);

    Tag(const Tag &_tag);

    Tag(GumboNode *_node);

    void MakeRoot(const std::string &_htmlCode);

    Tag& operator=(const Node &_node);

public:
    GumboNode* GetNode() const;

    GumboOutput* GetOutput();

    void SetNode(GumboNode *_node);

    void SetNode(Node _node);

public:
    std::string GetText() const;

    Tag FindTag(GumboTag _tag,
                const std::string &_attrName,
                const std::string &_attrValue) const;

    std::vector<Tag> FindAllTags(GumboTag _tag,
                                   const std::string &_attrName,
                                   const std::string &_attrValue);

    Tag FindTagAnyval(GumboTag _tag,
                      const std::string &_attrName,
                      const std::string &_attrValue) const;

    Tag FindTagAnysubval(GumboTag _tag,
                         const std::string &_attrName,
                         const std::string &_attrValue) const;

    std::vector<Tag> FindAllTagsAnyval(GumboTag _tag,
                                         const std::string &_attrName,
                                         const std::string &_attrValue) const;

    std::vector<Tag> FindAllTagsAnysubval(GumboTag _tag,
                                             const std::string &_attrName,
                                             const std::string &_attrValue) const;

    std::string GetHtmlView();

    Tag FindTagWithClassExc(GumboTag _targetTag, const std::string &_attrName,
                            const std::string &_attrValue,
                            const std::string &_excClass);

    Tag FindTagWithTagExc(GumboTag _targetTag, const std::string &_attrName,
                          const std::string &_attrValue,
                          const GumboTag &_excTag);

public:
    inline explicit operator bool() const {
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
