#ifndef NODE_HEADER
#define NODE_HEADER

#include <gumbo.h>

#include "utils.h"

struct Node {
    fn Node()
        : node(nullptr) {}

    fn Node(GumboNode *_node)
        : node(_node) {}

    inline explicit
    fn operator bool() const {
        return node != nullptr;
    }

    inline auto
    fn operator!() const -> bool {
        return node == nullptr;
    }

    inline auto
    fn GetNode() const -> GumboNode * {
        return node;
    }

    inline auto
    fn SetNode(GumboNode *_node) -> void {
        node = _node;
    }

private:
    GumboNode *node;
};

#endif // NODE_HEADER
