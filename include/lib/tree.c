#include "tree.h"


#ifndef NO_DEFINE_TREE_HEAD
const tree_node_t *const tn_head = NULL;
#endif


void add_child(tree_node_t *parent, tree_node_t *child) {
    child->parent = parent;
    if (parent->child == NULL) {
        parent->child = child;
        return;
    }
    tree_node_t *curr = parent->child;
    while (curr->next != NULL) {
        curr = curr->next;   
    }
    curr->next = child;
    child->prev = curr;
}

void add_next(tree_node_t *root, tree_node_t *next) {
    if (root->next == NULL) {
        root->next = next;
        next->prev = root;
        return;
    }

    tree_node_t *curr = root->next;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = next;
    next->prev = curr;
}


str_t node_to_str(tree_node_t *node) {
    str_t str = str_new();

    str_appendf(&str, "(P: 0x%p)->(C: 0x%p): \"%s\"", node->parent, node, node->value);
    str_appendf(&str, "    ");
    str_appendf(&str, "| (0x%p)->(C)->(0x%p)", node->prev, node->next);

    str_end(&str, NULL);
    return str;
}

str_t debug_tree_to_str(tree_node_t *root) {
    str_t str = str_new();

    tree_node_t *node = root;
    while (node != NULL) {
        str_appendf(&str, "=> %s\n", node_to_str(node).str);
        tree_node_t *curr = node->child;
        while (curr != NULL) {
            str_appendf(&str, "   -> %s\n", node_to_str(curr).str);
            curr = curr->next;
        }
        node = node->next;
    }

    str_end(&str, NULL);
    return str;
}

str_t tree_to_str(tree_node_t *root, int idx, int spacing) {
    str_t str = str_new();
    if (root == NULL) {
        return (str_t){.len = 0, .str = NULL};
    }

    tree_node_t *node = root;
    while (node != NULL) {
        str_appendf(&str, "%*s%s\n", idx, "", node->value);
        str_t tree = tree_to_str(node->child, idx+spacing, spacing);
        if (tree.str != NULL) {
            str_appendf(&str, "%s", tree.str);
        }

        node = node->next;
    }

    str_end(&str, NULL);
    return str;
}
