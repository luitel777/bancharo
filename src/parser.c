#include "parser.h"

AST_NODE **parse_syntax() {
        AST_NODE **tree_node = malloc(sizeof(AST_NODE));
        AST_NODE *local_node = malloc(sizeof(AST_NODE));

        *local_node = expr();
        *tree_node = local_node;
        while ((local_node)->left != NULL) {
                (local_node) = (local_node)->left;
        }

        local_node->left = make_node(RET, "next instruction");
        return &(*tree_node);
}

AST_NODE expr() {
        bool correct = false;
        AST_NODE **node = malloc(sizeof(AST_NODE));
        identify_tokens();

        if (check_operation(&(*node)) || check_setq(&(*node)) ||
            check_while(&(*node)) || check_print(&(*node))) {
                correct = true;
        } else {
                printf("Invalid syntax, quitting\n");
                exit(0);
                correct = false;
        }
        identify_next_character();
        return (**node);
}

bool check_setq(AST_NODE **setq_node) {
        int32_t prev_pointer = char_pointer;
        int32_t prev_line = lines;
        struct AST_NODE *node = malloc(sizeof(AST_NODE));

        identify_tokens();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                setq_node = NULL;
                return false;
        }
        identify_next_character();

        if (tokens != SETQ) {
                reset_buf(&prev_pointer, &prev_line);
                setq_node = NULL;
                return false;
        }

        right_ast_node("setq", SETQ, &node);
        identify_next_character();

        if (tokens != IDENT) {
                reset_buf(&prev_pointer, &prev_line);
                setq_node = NULL;
                return false;
        }
        right_ast_node(value, DIGIT, &node->right);
        identify_next_character();

        if (tokens == DIGIT || tokens == IDENT) {
                if (tokens == DIGIT) {
                        int32_t digit = get_number();
                        char buffer[256];
                        snprintf(buffer, 256, "%d", digit);
                        left_ast_node(buffer, DIGIT, &node->right);
                }
        } else {
                reset_buf(&prev_pointer, &prev_line);
                setq_node = NULL;
                return false;
        }
        identify_next_character();
        if (tokens != S_R_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                setq_node = NULL;
                return false;
        }
        *setq_node = node->right;
        return true;
}

bool check_operation(AST_NODE **opr_node) {
        int32_t prev_pointer = char_pointer;
        int32_t prev_line = lines;
        int32_t digit = 0;
        char buffer[256];
        struct AST_NODE *node = malloc(sizeof(AST_NODE));

        identify_tokens();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                opr_node = NULL;
                return false;
        }
        identify_next_character();

        // make new node
        // node->right
        if (!is_opr()) {
                reset_buf(&prev_pointer, &prev_line);
                opr_node = NULL;
                return false;
        }
        if (tokens == ADD) {
                right_ast_node("+", ADD, &node);
        } else {
                right_ast_node("-", SUB, &node);
        }
        identify_next_character();

        // node->right->val = rational
        if (tokens == DIGIT || tokens == IDENT) {
                if (tokens == DIGIT) {
                        digit = get_number();
                        snprintf(buffer, 256, "%d", digit);
                        right_ast_node(buffer, DIGIT, &node->right);
                }
                if (tokens == IDENT) {
                        right_ast_node(value, IDENT, &node->right);
                }
        } else {
                reset_buf(&prev_pointer, &prev_line);
                opr_node = NULL;
                return false;
        }
        identify_next_character();

        // node->right->val = NULL
        // create on node->left
        if (tokens == DIGIT || tokens == IDENT) {
                if (tokens == DIGIT) {
                        digit = get_number();
                        snprintf(buffer, 256, "%d", digit);
                        left_ast_node(buffer, DIGIT, &node->right);
                }
                if (tokens == IDENT) {
                        left_ast_node(value, IDENT, &node->right);
                }
        } else {
                reset_buf(&prev_pointer, &prev_line);
                opr_node = NULL;
                return false;
        }
        identify_next_character();

        // next character will be )
        if (tokens != S_R_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                opr_node = NULL;
                return false;
        }
        *opr_node = node->right;
        return true;
}

bool check_function(AST_NODE **function_node) {
        int32_t prev_pointer = char_pointer;
        int32_t prev_line = lines;

        identify_tokens();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();

        if (tokens != DEFUN) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();

        if (tokens != IDENT) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();
        if (tokens != S_R_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();

        if (check_setq(function_node) || check_operation(function_node)) {
        } else {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();
        return true;
}

bool check_while(AST_NODE **while_node) {
        int32_t prev_pointer = char_pointer;
        int32_t prev_line = lines;

        identify_tokens();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();

        // create node->value = while
        if (tokens != WHILE) {
                reset_buf(&prev_pointer, &prev_line);
                return false;
        }
        identify_next_character();

        {

                int32_t digit = 0;
                char buffer[256];
                struct AST_NODE *node = malloc(sizeof(AST_NODE));

                if (tokens != S_L_PAREN) {
                        reset_buf(&prev_pointer, &prev_line);
                        return false;
                }
                identify_next_character();

                // create node->left->value = >
                if (tokens == GREATER || tokens == LESSER) {
                        if (tokens == GREATER) {
                                right_ast_node(">", GREATER, &node);
                        }
                        if (tokens == LESSER) {
                                right_ast_node("<", LESSER, &node);
                        }

                } else {
                        reset_buf(&prev_pointer, &prev_line);
                        return false;
                }
                identify_next_character();

                // create node->left->left->value =
                if (tokens == DIGIT || tokens == IDENT) {
                        if (tokens == DIGIT) {
                                digit = get_number();
                                snprintf(buffer, 256, "%d", digit);
                                right_ast_node(buffer, DIGIT, &node->right);
                        }
                        if (tokens == IDENT) {
                                right_ast_node(value, IDENT, &node->right);
                        }
                } else {
                        reset_buf(&prev_pointer, &prev_line);
                        return false;
                }
                identify_next_character();

                // create node->left->right->value =
                if (tokens == DIGIT || tokens == IDENT) {
                        if (tokens == DIGIT) {
                                digit = get_number();
                                snprintf(buffer, 256, "%d", digit);
                                left_ast_node(buffer, DIGIT, &node->right);
                        }
                        if (tokens == IDENT) {
                                left_ast_node(value, IDENT, &node->right);
                        }
                } else {
                        reset_buf(&prev_pointer, &prev_line);
                        return false;
                }

                identify_next_character();
                if (tokens != S_R_PAREN) {
                        printf("error mismatched braces\n");
                        reset_buf(&prev_pointer, &prev_line);
                        return false;
                }
                *while_node = node->right;
        }
        AST_NODE **while_temp_node = malloc(sizeof(AST_NODE));

        identify_next_character();

        // this follows same principle of joining trees like in
        // bancharo.c
        AST_NODE *s_node = malloc(sizeof(AST_NODE));
        AST_NODE *p_node = malloc(sizeof(AST_NODE));

        // temp node instead of working directly
        // on out while_node
        AST_NODE *t_node = malloc(sizeof(AST_NODE));
        AST_NODE **t_p_node = malloc(sizeof(AST_NODE));

        (*t_p_node) = p_node;
        while (check_operation(while_temp_node)) {
                while ((p_node)->left != NULL) {
                        (p_node) = (p_node)->left;
                }

                s_node = *while_temp_node;
                (p_node)->left = (s_node);
                identify_next_character();
        }

        if (tokens != S_R_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                free(t_p_node);
                free(t_node);
                free(s_node);
                free(p_node);
                return false;
        }

        memcpy(t_node, *t_p_node, sizeof(AST_NODE));
        *while_temp_node = t_node;

        *while_temp_node = (*while_temp_node)->left;
        (*while_node)->left->left = (*while_temp_node);

        free(t_p_node);
        free(t_node);
        free(while_temp_node);
        return true;
}

bool check_print(AST_NODE **print_node) {
        int32_t prev_pointer = char_pointer;
        int32_t prev_line = lines;
        struct AST_NODE *node = malloc(sizeof(AST_NODE));

        identify_tokens();
        if (tokens != S_L_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                print_node = NULL;
                return false;
        }
        identify_next_character();

        if (tokens != PRINT) {
                reset_buf(&prev_pointer, &prev_line);
                print_node = NULL;
                return false;
        }
        right_ast_node("print", PRINT, &node);
        // this creates the one and only needed node
        identify_next_character();

        if (tokens == IDENT || tokens == DIGIT) {
                if (tokens == DIGIT) {
                        int32_t digit = get_number();
                        char buffer[256];
                        snprintf(buffer, 256, "%d", digit);
                        left_ast_node(buffer, DIGIT, &node->right);
                } else if (tokens == IDENT) {
                        left_ast_node(value, IDENT, &node->right);
                }
        } else {
                reset_buf(&prev_pointer, &prev_line);
                print_node = NULL;
                return false;
        }
        // empty node
        // I have no clue why removing this will make print dissappear
        // in our codegen
        left_ast_node("", PRINT, &node->right);
        identify_next_character();

        if (tokens != S_R_PAREN) {
                reset_buf(&prev_pointer, &prev_line);
                print_node = NULL;
                return false;
        }
        next_buf();

        *print_node = node->right;

        return true;
}

void identify_next_character() {
        next_buf();
        identify_tokens();
}
void reset_buf(int32_t *prev_pointer, int32_t *prev_line) {
        char_pointer = *prev_pointer;
        lines = *prev_line;
        set_buf(*prev_pointer);
}