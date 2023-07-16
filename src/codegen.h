#ifndef __BANCHARO_CODEGEN_H__
#define __BANCHARO_CODEGEN_H__

#include "ast.h"
#include "hashmap.h"

void parse_tree(AST_NODE **node);

void asm_add(TABLE val1, TABLE val2);
void asm_setq(TABLE val1, TABLE val2);
void asm_greater(TABLE val1, TABLE val2);
void asm_gen_label(AST_NODE **node, TABLE val1, TABLE val2);
void asm_print(TABLE val1);
void asm_cmp(TABLE val1, TABLE val2);
char *convert_offset(char *val);
void front_boilerplate();
void end_boilerplate();

#endif
