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
        TABLE temp;

        char *val1 = malloc(sizeof(char) * 256);
        char *val2 = malloc(sizeof(char) * 256);
        char *val3 = malloc(sizeof(char) * 256);

        if ((*node) != NULL) {
                if ((*node)->right != NULL) {
                        TABLE val1;
                        val1.value = (*node)->left->value;
                        val1.token = (*node)->left->token;

                        TABLE val2;
                        val2.value = (*node)->right->value;
                        val2.token = (*node)->right->token;

                        switch ((*node)->token) {
                        case ADD:
                                if (val2.token == IDENT) {
                                        val2.value = convert_offset(val2.value);
                                }
                                if (val1.token == IDENT) {
                                        val1.value = convert_offset(val1.value);
                                }
                                asm_add(val1.value, val2.value);
                                break;
                        case LESSER:
                                if (val2.token == IDENT) {
                                        val2.value = convert_offset(val2.value);
                                }
                                if (val1.token == IDENT) {
                                        val1.value = convert_offset(val1.value);
                                }
                                printf("label:\n");
                                asm_gen_label(node, &val1, &val2);
                                asm_cmp(val1.value, val2.value);
                                printf("jl label\n");
                                break;
                        case SETQ:
                                insert_symbol(val2.value);
                                val2.value = convert_offset(val2.value);
                                asm_setq(val1.value, val2.value);
                                break;
                        case PRINT:
                                if (val2.token == IDENT) {
                                        val2.value = convert_offset(val2.value);
                                }
                                if (val1.token == IDENT) {
                                        val1.value = convert_offset(val1.value);
                                }
                                asm_print(val1.value);
                                break;
                        }
                        if ((*node)->left->left->token == RET) {
                                printf("\n");
                        }
                }
                parse_tree(&(*node)->left);
        }
}

void asm_add(char *val1, char *val2) { printf("add %s, %s\n", val2, val1); }

void asm_cmp(char *val1, char *val2) { printf("cmp %s, %s\n", val1, val2); }

void asm_setq(char *val1, char *val2) {
        printf("mov eax, %s\n", val1);
        printf("mov %s, eax\n", val2);
}

void asm_greater(char *val1, char *val2) {
        printf("mov rax %s\n", val1);
        printf("mov rbx %s\n", val2);
}

void asm_gen_label(AST_NODE **node, TABLE *val1, TABLE *val2) {
        while ((*node)->left->left->token != RET) {
                if ((*node)->left->token == IDENT ||
                    (*node)->left->token == DIGIT) {
                } else {
                        val1->value = (*node)->left->left->value;
                        val2->value = (*node)->left->right->value;

                        val1->token = (*node)->left->left->token;
                        val2->token = (*node)->left->right->token;

                        if (val2->token == IDENT) {
                                val2->value = convert_offset(val2->value);
                        }
                        if (val1->token == IDENT) {
                                val1->value = convert_offset(val1->value);
                        }
                        asm_add(val1->value, val2->value);
                }
                (*node) = (*node)->left;
        }
}

void asm_print(char *val) {
        printf("mov rax, 0\n");
        printf("mov rdi, format_int\n");
        printf("mov rsi, %s\n", val);
        printf("call printf\n");
}
char *convert_offset(char *val) {
        // [store + ]
        TABLE *tempa = retrive_symbol(val);
        char *value = malloc(sizeof(char) * 256);
        snprintf(value, 256, "[store + %d]", tempa->size_value);
        return value;
}
