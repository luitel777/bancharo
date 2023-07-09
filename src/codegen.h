#ifndef __BANCHARO_CODEGEN_H__
#define __BANCHARO_CODEGEN_H__

#include "ast.h"

void parse_tree(AST_NODE **node);

void asm_add(char *val1, char *val2);
void asm_setq(char *val1, char *val2);
void asm_greater(char *val1, char *val2);
void asm_gen_label(AST_NODE **node, char *val1, char *val2);

#endif
