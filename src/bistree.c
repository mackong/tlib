#include <stdlib.h>
#include <string.h>

#include "bistree.h"

#define node_factor(node) (((AvlNode *)bitree_data(node))->factor)
#define node_data(node) (((AvlNode *)bitree_data(node))->data)
#define node_hidden(node) (((AvlNode *)bitree_data(node))->hidden)

static void rotate_left(BiTreeNode **node)
{
        BiTreeNode *left, *grandchild;

        left = bitree_left(*node);

        if (node_factor(left) == AVL_LEFT_HEAVY) {
                /* LL */
                bitree_left(*node) = bitree_right(left);
                bitree_right(left) = *node;
                node_factor(*node) = AVL_BALANCED;
                node_factor(left) = AVL_BALANCED;
                *node = left;
        } else {
                /* LR */
                grandchild = bitree_right(left);
                bitree_right(left) = bitree_left(grandchild);
                bitree_left(grandchild) = left;
                bitree_left(*node) = bitree_right(grandchild);
                bitree_right(grandchild) = *node;

                switch (node_factor(grandchild)) {
                case AVL_LEFT_HEAVY:
                        node_factor(*node) = AVL_RIGHT_HEAVY;
                        node_factor(left) = AVL_BALANCED;
                        break;
                case AVL_BALANCED:
                        node_factor(*node) = AVL_BALANCED;
                        node_factor(left) = AVL_BALANCED;
                        break;
                case AVL_RIGHT_HEAVY:
                        node_factor(*node) = AVL_BALANCED;
                        node_factor(left) = AVL_LEFT_HEAVY;
                        break;
                }

                node_factor(grandchild) = AVL_BALANCED;
                *node = grandchild;
        }
}

static void rotate_right(BiTreeNode **node)
{
        BiTreeNode *right, *grandchild;

        right = bitree_right(*node);

        if (node_factor(right) == AVL_RIGHT_HEAVY) {
                /* RR */
                bitree_right(*node) = bitree_left(right);
                bitree_left(right) = *node;
                node_factor(*node) = AVL_BALANCED;
                node_factor(right) = AVL_BALANCED;
                *node = right;
        } else {
                /* RL */
                grandchild = bitree_left(right);
                bitree_left(right) = bitree_right(grandchild);
                bitree_right(grandchild) = right;
                bitree_right(*node) = bitree_left(grandchild);
                bitree_left(grandchild) = *node;

                switch (node_factor(grandchild)) {
                case AVL_LEFT_HEAVY:
                        node_factor(*node) = AVL_BALANCED;
                        node_factor(right) = AVL_RIGHT_HEAVY;
                        break;
                case AVL_BALANCED:
                        node_factor(*node) = AVL_BALANCED;
                        node_factor(right) = AVL_BALANCED;
                        break;
                case AVL_RIGHT_HEAVY:
                        node_factor(*node) = AVL_LEFT_HEAVY;
                        node_factor(right) = AVL_BALANCED;
                        break;
                }

                node_factor(grandchild) = AVL_BALANCED;
                *node = grandchild;
        }
}

static void destroy_left(BisTree *tree, BiTreeNode *node);
static void destroy_right(BisTree *tree, BiTreeNode *node);

static void destroy(BisTree *tree, BiTreeNode *node, int dir)
{
        BiTreeNode **position;

        if (bitree_size(tree) == 0) {
                return;
        }

        if (node == NULL) {
                position = &tree->root;
        } else {
                if (dir == 0) {
                        position = &node->left;
                } else {
                        position = &node->right;
                }
        }

        if (*position != NULL) {
                destroy_left(tree, *position);
                destroy_right(tree, *position);

                if (tree->destroy) {
                        tree->destroy(node_data(*position));
                }

                free((*position)->data);
                free(*position);
                *position = NULL;

                tree->size--;
        }
}

static void destroy_left(BisTree *tree, BiTreeNode *node)
{
        destroy(tree, node, 0);
}

static void destroy_right(BisTree *tree, BiTreeNode *node)
{
        destroy(tree, node, 1);
}

static int insert(BisTree *tree, BiTreeNode **node,
                  const void *data, int *balanced)
{
        AvlNode *avl_data;
        int cmpval, retval;

        if (bitree_is_eob(*node)) {
                avl_data = (AvlNode *)malloc(sizeof(AvlNode));
                if (!avl_data) {
                        return -1;
                }

                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;

                return bitree_ins_left(tree, *node, avl_data);
        } else {
                cmpval = tree->compare(data, node_data(*node));
                if (cmpval < 0) {
                        /* To left */
                        if (bitree_is_eob(bitree_left(*node))) {
                                avl_data = (AvlNode *)malloc(sizeof(AvlNode));
                                if (!avl_data) {
                                        return -1;
                                }

                                avl_data->factor = AVL_BALANCED;
                                avl_data->hidden = 0;
                                avl_data->data = (void *)data;

                                if (bitree_ins_left(tree, *node, avl_data) != 0) {
                                        return -1;
                                }

                                *balanced = 0;
                        } else {
                                retval = insert(tree, &bitree_left(*node), data, balanced);
                                if (retval != 0) {
                                        return retval;
                                }
                        }

                        if (!(*balanced)) {
                                switch (node_factor(*node)) {
                                case AVL_LEFT_HEAVY:
                                        rotate_left(node);
                                        *balanced = 1;
                                        break;
                                case AVL_BALANCED:
                                        node_factor(*node) = AVL_LEFT_HEAVY;
                                        break;
                                case AVL_RIGHT_HEAVY:
                                        node_factor(*node) = AVL_BALANCED;
                                        *balanced = 1;
                                        break;
                                }
                        }
                } else if (cmpval > 0) {
                        if (bitree_is_eob(bitree_right(*node))) {
                                avl_data = (AvlNode *)malloc(sizeof(AvlNode));
                                if (!avl_data) {
                                        return -1;
                                }

                                avl_data->factor = AVL_BALANCED;
                                avl_data->hidden = 0;
                                avl_data->data = (void *)data;

                                if (bitree_ins_right(tree, *node, avl_data) != 0) {
                                        return -1;
                                }

                                *balanced = 0;
                        } else {
                                retval = insert(tree, &bitree_right(*node), data, balanced);
                                if (retval != 0) {
                                        return retval;
                                }
                        }

                        if (!(*balanced)) {
                                switch(node_factor(*node)) {
                                case AVL_LEFT_HEAVY:
                                        node_factor(*node) = AVL_BALANCED;
                                        *balanced = 1;
                                        break;
                                case AVL_BALANCED:
                                        node_factor(*node) = AVL_RIGHT_HEAVY;
                                        break;
                                case AVL_RIGHT_HEAVY:
                                        rotate_right(node);
                                        *balanced = 1;
                                        break;
                                }
                        }
                } else {
                        if (!node_hidden(*node)) {
                                return 1;
                        } else {
                                if (tree->destroy) {
                                        tree->destroy(node_data(*node));
                                }

                                node_data(*node) = (void *)data;
                                node_hidden(*node) = 0;

                                *balanced = 1;
                        }
                }
        }

        return 0;
}

static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
        int cmpval, retval;

        if (bitree_is_eob(node)) {
                return -1;
        }

        cmpval = tree->compare(data, node_data(node));
        if (cmpval < 0) {
                retval = hide(tree, bitree_left(node), data);
        } else if (cmpval > 0) {
                retval = hide(tree, bitree_right(node), data);
        } else {
                node_hidden(node) = 1;
                retval = 0;
        }

        return retval;
}

static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
        int cmpval, retval;

        if (bitree_is_eob(node)) {
                return -1;
        }

        cmpval = tree->compare(*data, node_data(node));
        if (cmpval < 0) {
                retval = lookup(tree, bitree_left(node), data);
        } else if (cmpval > 0) {
                retval = lookup(tree, bitree_right(node), data);
        } else {
                if (!node_hidden(node)) {
                        *data = node_data(node);
                        retval = 0;
                } else {
                        return -1;
                }
        }

        return retval;
}

int bistree_init(BisTree *tree, fp_compare compare, fp_destroy destroy)
{
        if (bitree_init(tree, destroy) != 0) {
                return -1;
        }
        tree->compare = compare;

        return 0;
}

int bistree_destroy(BisTree *tree)
{
        destroy_left(tree, NULL);

        memset(tree, 0, sizeof(BisTree));

        return 0;
}

int bistree_insert(BisTree *tree, const void *data)
{
        int balanced = 0;
        return insert(tree, &bitree_root(tree), data, &balanced);
}

int bistree_remove(BisTree *tree, const void *data)
{
        return hide(tree, bitree_root(tree), data);
}

int bistree_lookup(BisTree *tree, void **data)
{
        return lookup(tree, bitree_root(tree), data);
}

static void preorder_dump(BiTreeNode *node, fp_dump dump)
{
        if (!bitree_is_eob(node)) {
                if (!node_hidden(node)) {
                        dump(node_data(node));
                }

                preorder_dump(bitree_left(node), dump);
                preorder_dump(bitree_right(node), dump);
        }
}

static void inorder_dump(BiTreeNode *node, fp_dump dump)
{
        if (!bitree_is_eob(node)) {
                inorder_dump(bitree_left(node), dump);

                if (!node_hidden(node)) {
                        dump(node_data(node));
                }

                inorder_dump(bitree_right(node), dump);
        }
}

static void postorder_dump(BiTreeNode *node, fp_dump dump)
{
        if (!bitree_is_eob(node)) {
                postorder_dump(bitree_left(node), dump);
                postorder_dump(bitree_right(node), dump);

                if (!node_hidden(node)) {
                        dump(node_data(node));
                }
        }
}

void bistree_preorder_dump(BisTree *tree, fp_dump dump)
{
        if (!dump) {
                return;
        }

        preorder_dump(tree->root, dump);
}

void bistree_inorder_dump(BisTree *tree, fp_dump dump)
{
        if (!dump) {
                return;
        }

        inorder_dump(tree->root, dump);
}

void bistree_postorder_dump(BisTree *tree, fp_dump dump)
{
        if (!dump) {
                return;
        }

        postorder_dump(tree->root, dump);
}
