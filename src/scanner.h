#ifndef __BANCHARO_SCANNER__H__
#define __BANCHARO_SCANNER__H__

#include "bancharo.h"
#include "tokens.h"

char next_buf();
char prev_buf();
bool is_digit();
void skip_newline();
int64_t get_number();
// char to int_64
int64_t ctoi64(char val);
bool is_keyword();
TOKENS identify_tokens();
bool is_opr();
void set_buf(int32_t location);
bool is_char();
bool is_print();
char *give_identifier();
#endif
