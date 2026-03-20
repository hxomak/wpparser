#ifndef NODE_HEADER
#define NODE_HEADER

#include <gumbo.h>

#include "utils.h"

struct Node {
    Node()
        : node(nullptr) {}

    Node(GumboNode *_node)
        : node(_node) {}

    inline explicit operator bool() const {
        return node != nullptr;
    }

    inline bool operator!() const {
        return node == nullptr;
    }

    inline GumboNode* GetNode() const {
        return node;
    }

    inline void SetNode(GumboNode *_node) {
        node = _node;
    }

private:
    GumboNode *node;
};

#endif // NODE_HEADER
