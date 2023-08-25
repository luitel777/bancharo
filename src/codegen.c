#include "codegen.h"
#include "scanner.h"

int32_t label_counter = 0;
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

        if ((*node) != NULL) {
                if ((*node)->right != NULL) {
                        TABLE val1;
                        val1.value = (*node)->left->value;
                        val1.token = (*node)->left->token;

                        TABLE val2;
                        val2.value = (*node)->right->value;
                        val2.token = (*node)->right->token;

                        switch ((*node)->token) {
                        case SUB:
                                asm_sub(val1, val2);
                        case ADD:
                                asm_add(val1, val2);
                                break;
                        case MUL:
                                asm_mul(val1, val2);
                                break;
                        case DIV:
                                asm_div(val1, val2);
                                break;
                        case LESSER:
                                label_counter++;
                                printf("mov eax, %s\n", val1.value);
                                printf("label_%d:\n", label_counter);
                                asm_gen_label(node, val1, val2);
                                asm_cmp(val1, val2);
                                printf("jl label_%d\n", label_counter);
                                break;
                        case GREATER:
                                label_counter++;
                                printf("mov eax, %s\n", val1.value);
                                printf("label_%d:\n", label_counter);
                                asm_gen_label(node, val1, val2);
                                asm_cmp(val1, val2);
                                printf("jg label_%d\n", label_counter);
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
        free(val1);
        free(val2);
}

void asm_add(TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
                printf("mov edx, %s\n", val1.value);
                printf("add %s, edx\n", val2.value);
        } else if (val1.token == IDENT) {
                // (+ DIGIT IDENT) is kinda unnecessary but allowed by syntax so
                // we ignore this
        } else {
                // Do nothing cuz you are not using that value anyway
        }
}

void asm_mul(TABLE val1, TABLE val2) {
        // (* abc 12)

        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);

                // we save the existing value of rax and rbx in r8
                printf("mov r8, rax\n");
                printf("mov r9, rbx\n");

                // we load our value in rax and rbx
                printf("mov rax, %s\n", val1.value);
                printf("mov rbx, %s\n", val2.value);

                // we multiply next
                printf("imul rbx\n");

                // we load rax in our value
                printf("mov %s, rax\n", val2.value);

                // reset rax to old status
                printf("mov rax, r8\n");
                printf("mov rbx, r9\n");

        } else if (val1.token == IDENT) {
                // (* DIGIT IDENT) is kinda unnecessary but allowed by syntax so
                // we ignore this
        } else {
                // Do nothing cuz you are not using that value anyway
        }
}

void asm_div(TABLE val1, TABLE val2) {

        // (/ IDENT DIGIT)

        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);

                // we save the existing value of rax, rbx and rdx
                printf("mov r8, rax\n"); // divident low
                printf("mov r9, rbx\n"); // divisor
                printf("mov r11, rdx\n"); // divident high
                // quoitent is stored in rax

                // we load our value in eax and ebx
                printf("mov rdx, 0\n");
                printf("mov rbx, %s\n", val1.value);
                printf("mov rax, %s\n", val2.value);

                // we divide next
                printf("div rbx\n");

                // we load rax (quoitent) in our value
                printf("mov %s, rax\n", val2.value);

                // reset rax to old status
                printf("mov rax, r8\n");
                printf("mov rbx, r9\n");
                printf("mov rdx, r11\n");
        } else if (val1.token == IDENT) {
                // (/ DIGIT IDENT) is kinda unnecessary but allowed by syntax so
                // we ignore this
        } else {
                // Do nothing cuz you are not using that value anyway
        }
}

void asm_sub(TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
                printf("mov edx, %s\n", val1.value);
                printf("sub %s, edx\n", val2.value);
        } else if (val1.token == IDENT) {
                // (- DIGIT IDENT) is kinda unnecessary but allowed by syntax so
                // we ignore this
        } else {
                // Do nothing cuz you are not using that value anyway
        }
}

void asm_cmp(TABLE val1, TABLE val2) {
        if (val2.token == IDENT) {
                val2.value = convert_offset(val2.value);
        }
        if (val1.token == IDENT) {
                val1.value = convert_offset(val1.value);
        }
        printf("mov edx, %s\n", val2.value);
        printf("cmp edx, eax\n");
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
                        if ((*node)->left->token == ADD) {
                                asm_add(val1, val2);
                        } else if ((*node)->left->token == SUB) {
                                asm_sub(val1, val2);
                        } else if ((*node)->left->token == MUL) {
                                asm_mul(val1, val2);
                        } else if ((*node)->left->token == DIV) {
                                asm_div(val1, val2);
                        } else if ((*node)->left->token == PRINT) {
                                asm_print(val1);
                        }
                }
                (*node) = (*node)->left;
        }
}

void asm_print(TABLE val) {
        if (val.token == IDENT) {
                val.value = convert_offset(val.value);
        }
        // eax is lower 32 bit of rax so changing rax to 0
        // will change eax to 0 as well
        printf("mov ebx, eax\n");
        printf("mov rax, 0\n");
        printf("mov rdi, format_int\n");
        printf("mov rsi, %s\n", val.value);
        printf("call printf\n");
        printf("mov eax, ebx\n");
}
char *convert_offset(char *val) {
        // [store + ]
        TABLE *tempa = retrive_symbol(val);
        char *value = malloc(sizeof(char) * 256);
        snprintf(value, 256, "[store + %d]", tempa->size_value);
        return value;
}

void front_boilerplate() {
        printf("extern printf\n");
        printf("bits 64\n");
        printf("\n");
        printf("section .bss\n");
        printf("store resb 1\n");
        printf("\n");
        printf("section .data\n");
        printf("format_int dw \"%%d\", 10, 0\n");
        printf("\n");
        printf("section .text\n");
        printf("global main\n");
        printf("\n");
        printf("main:\n");
}

void end_boilerplate() {
        printf("mov rdi, 0\n");
        printf("mov rax, 60\n");
        printf("syscall\n");
}
