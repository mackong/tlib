#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/* Balance factor */
#define AVL_LEFT_HEAVY  1
#define AVL_BALANCED    0
#define AVL_RIGHT_HEAVY -1

typedef struct AvlNode_ {
        void *data;
        int hidden;
        int factor;
} AvlNode;

typedef BiTree BisTree;

int bistree_init(BisTree *tree, fp_compare compare, fp_destroy destroy);
int bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);

void bistree_preorder_dump(BisTree *tree, fp_dump dump);
void bistree_inorder_dump(BisTree *tree, fp_dump dump);
void bistree_postorder_dump(BisTree *tree, fp_dump dump);

#define bistree_size(tree) ((tree)->size)

#endif /* BISTREE_H */
