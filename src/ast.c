#include "parser.h"

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
#if 1
        while (*p_tree != NULL) {
                printf("%s\t%d\n", (*p_tree)->value, (*p_tree)->token);
                if ((*p_tree)->right != NULL) {
                        printf("%s\t%d\n", (*p_tree)->right->value,
                               (*p_tree)->right->token);
                }
                (*p_tree) = (*p_tree)->left;
        }
#endif

#if 0
        if ((*node) == NULL)
                return;
        parse_tree(&(*node)->left);
        parse_tree(&(*node)->right);
        printf("%s\n", (*node)->value);
#endif
}
