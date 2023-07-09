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

        char *val1 = malloc(sizeof(char) * 256);
        char *val2 = malloc(sizeof(char) * 256);
        char *val3 = malloc(sizeof(char) * 256);

        if ((*node) != NULL) {
                if ((*node)->right != NULL) {
                        val1 = (*node)->left->value;
                        val2 = (*node)->right->value;
                        switch ((*node)->token) {
                        case ADD:
                                asm_add(val1, val2);
                                break;
                        case LESSER:
                                asm_greater(val1, val2);
                                printf("label:\n");
                                asm_gen_label(node, val1, val2);
                                printf("jl label\n");
                                break;
                        case SETQ:
                                asm_setq(val1, val2);
                                break;
                        }
                        if ((*node)->left->left->token == RET) {
                                printf("RET\n\n");
                        }
                }
                parse_tree(&(*node)->left);
        }
}

void asm_add(char *val1, char *val2) {
        printf("mov rax, %s\n", val1);
        printf("mov rbx, %s\n", val2);
        printf("add rax, rbx\n\n");
}

void asm_setq(char *val1, char *val2) { printf("mov rax, %s\n", val1); }

void asm_greater(char *val1, char *val2) {
        printf("mov %s rax\n", val1);
        printf("mov %s rax\n", val2);
}

void asm_gen_label(AST_NODE **node, char *val1, char *val2) {
        while ((*node)->left->left->token != RET) {
                if ((*node)->left->token == IDENT ||
                    (*node)->left->token == DIGIT) {
                } else {
                        val1 = (*node)->left->left->value;
                        val2 = (*node)->left->right->value;
                        asm_add(val1, val2);
                }
                (*node) = (*node)->left;
        }
}
