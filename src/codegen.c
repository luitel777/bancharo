#include "codegen.h"
#include "scanner.h"

void parse_tree(AST_NODE **node) {
#if 1
        while (*node != NULL) {
                printf("%s\t%d\n", (*node)->value, (*node)->token);
                if ((*node)->right != NULL) {
                        printf("%s\t%d\n", (*node)->right->value,
                               (*node)->right->token);
                }
                (*node) = (*node)->left;
        }
#endif
}
