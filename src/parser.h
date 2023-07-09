#ifndef __BANCHARO_PARSER_H__
#define __BANCHARO_PARSER_H__

#include "ast.h"
#include "bancharo.h"
#include "scanner.h"

// parser checks the statement and
// fill in our tree node

AST_NODE expr();
bool check_operation(AST_NODE **node);
bool check_assign(AST_NODE **node);
bool check_setq(AST_NODE **node);
bool check_while(AST_NODE **node);
bool check_function(AST_NODE **node);
bool check_print(AST_NODE **node);
void identify_next_character();
void reset_buf(int32_t *prev_pointer, int32_t *prev_line);
AST_NODE **parse_syntax();

#endif