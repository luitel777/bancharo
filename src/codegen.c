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
                                asm_add(val1, val2);
                                break;
                        case LESSER:
                                printf("label:\n");
                                asm_gen_label(node, val1, val2);
                                asm_cmp(val1, val2);
                                printf("jl label\n");
                                break;
                        case SETQ:
                                insert_symbol(val2.value);
                                val2.value = convert_offset(val2.value);
                                asm_setq(val1, val2);
                                break;
                        case PRINT:
                                asm_print(val1);
                                break;
                        }
                        if ((*node)->left->left->token == RET) {
                                printf("\n");
                        }
                }
                parse_tree(&(*node)->left);
        }
}

void asm_add(TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
        }
        if (val1.token == IDENT) {
                val1.value = convert_offset(val1.value);
        }
        printf("add %s, %s\n", val2.value, val1.value);
}

void asm_cmp(TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
        }
        if (val1.token == IDENT) {
                val1.value = convert_offset(val1.value);
        }
        printf("cmp %s, %s\n", val1.value, val2.value);
}

void asm_setq(TABLE val1, TABLE val2) {
        printf("mov eax, %s\n", val1.value);
        printf("mov %s, eax\n", val2.value);
}

void asm_greater(TABLE val1, TABLE val2) {
        printf("mov rax %s\n", val1.value);
        printf("mov rbx %s\n", val2.value);
}

void asm_gen_label(AST_NODE **node, TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
        }
        if (val1.token == IDENT) {
                val1.value = convert_offset(val1.value);
        }
        while ((*node)->left->left->token != RET) {
                if ((*node)->left->token == IDENT ||
                    (*node)->left->token == DIGIT) {
                } else {
                        val1.value = (*node)->left->left->value;
                        val2.value = (*node)->left->right->value;

                        val1.token = (*node)->left->left->token;
                        val2.token = (*node)->left->right->token;

                        if (val2.token == IDENT) {
                                val2.value = convert_offset(val2.value);
                        }
                        if (val1.token == IDENT) {
                                val1.value = convert_offset(val1.value);
                        }
                        asm_add(val1, val2);
                }
                (*node) = (*node)->left;
        }
}

void asm_print(TABLE val) {
        if (val.token == IDENT) {
                val.value = convert_offset(val.value);
        }
        printf("mov rax, 0\n");
        printf("mov rdi, format_int\n");
        printf("mov rsi, %s\n", val.value);
        printf("call printf\n");
}
char *convert_offset(char *val) {
        // [store + ]
        TABLE *tempa = retrive_symbol(val);
        char *value = malloc(sizeof(char) * 256);
        snprintf(value, 256, "[store + %d]", tempa->size_value);
        return value;
}
