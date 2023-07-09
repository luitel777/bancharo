#include "codegen.h"
#include "scanner.h"

void parse_tree(AST_NODE **node) {
#if 0
        while (*node != NULL) {
                printf("%s\t%d\n", (*node)->value, (*node)->token);
                if ((*node)->right != NULL) {
                        printf("%s\t%d\n", (*node)->right->value,
                               (*node)->right->token);
                }
                (*node) = (*node)->left;
        }
#endif

        if ((*node) != NULL) {
                if ((*node)->right != NULL) {
                        printf("%s\n", (*node)->left->value);
                        printf("%s\n", (*node)->right->value);
                        printf("%s\n", (*node)->value);
                        if ((*node)->left->left->token == RET) {
                                printf("next instruction\n");
                        }
                }
                parse_tree(&(*node)->left);
        }
}
