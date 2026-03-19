<h1>WebPage Parser</h1>
This is a module for comfortable web-pages parsing. It provides convient API for curl and gumbo: extracting html code from web-page and any useful for you data from tags in html code.
<h2>There are class provided:</h2>
<b>Tag</b>
<h3>With following methods in it:</h3>

    fn Tag();

    fn Tag(const Node &_node);

    fn Tag(const Tag &_tag);

    fn Tag(GumboNode *_node);

    void MakeRoot(const std::string &_htmlCode);

    auto
    fn operator=(const Node &_node) -> Tag &;
    
    auto
    fn GetNode() const -> GumboNode *;

    GumboOutput *GetOutput();

    auto
    fn SetNode(GumboNode *_node) -> void;

    auto
    fn SetNode(Node _node) -> void;

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
    inline explicit
    fn operator bool() const;


<h1>How to compile</h1>
You are provided with CMakeLists.txt. You task is only to call cmake to compile:<br>
<code>cmake -S . -B build_debug -G "[your build system]" -DCMAKE_MAKE_PROGRAM="[path to your build system]"</code><br>
<code>cmake --build build_debug</code>
