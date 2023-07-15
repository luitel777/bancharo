#include "bancharo.h"

static int offset = 0;

struct TABLE {
        char *value;
        int token;
        int size_value;
} typedef TABLE;

struct SYMBOL_TABLE {
        struct TABLE tables[1024];
} typedef SYMBOL_TABLE;

extern SYMBOL_TABLE SYMBOLS;

void init_symbol_table();
void insert_symbol(char *value);
TABLE *retrive_symbol(char *value);