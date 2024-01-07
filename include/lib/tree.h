#pragma once

#include <stdio.h>
#include "str.h"

typedef struct tree_node {
    struct tree_node *parent,
                     *child,
                     *next,
                     *prev;

    char* value;
} tree_node_t;

#ifndef NO_DEFINE_TREE_HEAD
extern const tree_node_t *const tn_head;
#endif

#define MAKE_NODE(v) {  .parent = tn_head, .child = NULL,   \
                        .next = NULL, .prev = NULL,         \
                        .value = (v) }


void add_child(tree_node_t *parent, tree_node_t *child);
void add_next(tree_node_t *root, tree_node_t *next);

str_t node_to_str(tree_node_t *node);
str_t debug_tree_to_str(tree_node_t *root);
str_t tree_to_str(tree_node_t *root, int idx, int spacing);


