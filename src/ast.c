#include "parser.h"

AST_NODE *make_ast_tree(AST_NODE **node) {
        char_pointer = 0;
        set_buf(0);

        (*node) = malloc(sizeof(AST_NODE));
        while (current_char != 0) {
                next_buf();
                identify_tokens();
                if (check_operation(node)) {
                }
                return *node;
        };
}

AST_NODE *make_node(int token, char *value) {
        AST_NODE *new_node = (AST_NODE *)malloc(sizeof(AST_NODE));
        new_node->left = NULL;
        new_node->right = NULL;

        new_node->token = token;
        strcpy(new_node->value, value);
        if (new_node == NULL) {
                fprintf(stderr, "failed to create node\n");
                exit(0);
        }
        return new_node;
}

AST_NODE *right_ast_node(char *lexmes, int token, AST_NODE **node) {
        if ((*node) == NULL) {
                (*node) = make_node(token, lexmes);
                return *node;
        } else if ((*node)->right == NULL) {
                (*node)->right = right_ast_node(lexmes, token, &(*node)->right);
                return *node;
        } else {
                right_ast_node(lexmes, token, &(*node)->right);
        }
        return *node;
}

AST_NODE *left_ast_node(char *lexmes, int token, AST_NODE **node) {
        if ((*node) == NULL) {
                *node = make_node(token, lexmes);
                return *node;
        } else if ((*node)->left == NULL) {
                (*node)->left = left_ast_node(lexmes, token, &(*node)->left);
                return *node;
        } else if ((*node)->right == NULL) {
                (*node)->right = left_ast_node(lexmes, token, &(*node)->right);
        } else {
                left_ast_node(lexmes, token, &(*node)->right);
        }
        return *node;
}
void print_tree(AST_NODE **p_tree) {
        while (*p_tree != NULL) {
                printf("%s\n", (*p_tree)->value);
                if ((*p_tree)->right != NULL) {
                        printf("%s\n", (*p_tree)->right->value);
                }
                (*p_tree) = (*p_tree)->left;
        }
}
