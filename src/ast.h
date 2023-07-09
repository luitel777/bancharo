#include "bancharo.h"
#include "scanner.h"
#include "string.h"

struct AST_NODE {
        int token;
        char value[256];

        struct AST_NODE *left;
        struct AST_NODE *right;
} typedef AST_NODE;

AST_NODE *make_node(int token, char *value);
AST_NODE *right_ast_node(char *lexmes, int token, AST_NODE **node);
AST_NODE *left_ast_node(char *lexmes, int token, AST_NODE **node);
AST_NODE *make_ast_tree(AST_NODE **node);
