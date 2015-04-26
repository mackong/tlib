#include <stdlib.h>
#include <string.h>

#include "bitree.h"

int bitree_init(BiTree *tree, fp_destroy destroy)
{
        tree->size = 0;
        tree->root = NULL;
        tree->destroy = destroy;

        return 0;
}

int bitree_destroy(BiTree *tree)
{
        bitree_rem_left(tree, NULL);

        memset(tree, 0, sizeof(BiTree));

        return 0;
}

static int bitree_ins(BiTree *tree, BiTreeNode *node, const void *data, int dir)
{
                BiTreeNode *new_node, **position;

        if (node == NULL) {
                if (tree->size) {
                        return -1;
                }

                position = &tree->root;
        } else {
                if (dir == 0) {
                        if (node->left != NULL) {
                                return -1;
                        }

                        position = &node->left;
                } else {
                        if (node->right != NULL) {
                                return -1;
                        }

                        position = &node->right;
                }
        }

        if ((new_node = (BiTreeNode *) malloc(sizeof(BiTreeNode))) == NULL) {
                return -1;
        }

        new_node->data = (void *)data;
        new_node->left = NULL;
        new_node->right = NULL;

        *position = new_node;

        tree->size++;

        return 0;
}

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
        return bitree_ins(tree, node, data, 0);
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
        return bitree_ins(tree, node, data, 1);
}

static int bitree_rem(BiTree *tree, BiTreeNode *node, int dir)
{
        BiTreeNode **position;

        if (bitree_size(tree) == 0) {
                return -1;
        }

        if (!node) {
                position = &tree->root;
        } else {
                if (dir == 0) {
                        position = &node->left;
                } else {
                        position = &node->right;
                }
        }

        if (*position) {
                bitree_rem_left(tree, *position);
                bitree_rem_right(tree, *position);

                if (tree->destroy) {
                        tree->destroy((*position)->data);
                }

                free(*position);
                *position = NULL;

                tree->size--;
        }

        return 0;
}

int bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
        return bitree_rem(tree, node, 0);
}

int bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
        return bitree_rem(tree, node, 1);
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
        bitree_init(merge, left->destroy);

        if (bitree_ins_left(merge, NULL, data) != 0) {
                bitree_destroy(merge);
                return -1;
        }

        merge->root->left = left->root;
        merge->root->right = right->root;

        merge->size = left->size + right->size + 1;

        /* Do not let the original trees access the merged nodes. */
        left->root = NULL;
        left->size = 0;
        right->root = NULL;
        right->size = 0;

        return 0;
}
