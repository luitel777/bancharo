#ifndef __BANCHARO_CODEGEN_H__
#define __BANCHARO_CODEGEN_H__

#include "ast.h"
#include "hashmap.h"

void parse_tree(AST_NODE **node);

void asm_add(char *val1, char *val2);
void asm_setq(char *val1, char *val2);
void asm_greater(char *val1, char *val2);
void asm_gen_label(AST_NODE **node, TABLE *val1, TABLE *val2);
void asm_print(char *val1);
void asm_cmp(char *val1, char *val2);
char *convert_offset(char *val);

#endif
