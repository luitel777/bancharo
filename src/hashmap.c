#include "hashmap.h"

struct SYMBOL_TABLE *symbols = {0};
int32_t counter = 0;

void init_symbol_table() {
        symbols = malloc(sizeof(SYMBOL_TABLE));
        symbols->tables[0].value = "NULL";
}

int generate_hash(char *value) {
        int64_t len_value = (int)strlen(value);

        int32_t summation = 0;
        for (unsigned int i = 0; i < len_value; i++) {
                summation += value[i] << 1;
        }
        return summation % 900;
}

void insert_symbol(char *value) {
        int32_t index = generate_hash(value);
        if (symbols->tables[index].value != NULL) {
                if (!strcmp(symbols->tables[index].value, value)) {
                        printf("symbol \"%s\" already exists, ばかやろ？\n",
                               value);
                        exit(0);
                } else if (symbols->tables[index].value != NULL) {
                        // TODO: add linked list on collission
                        printf("conflicting values\n");
                        exit(0);
                }
        }
        counter += 1;
        symbols->tables[index].size_value = counter * 4;
        symbols->tables[index].value = value;
}

TABLE *retrive_symbol(char *value) {
        int32_t index = generate_hash(value);
        if (symbols->tables[index].value != NULL) {
                // printf("offset is %d \n", symbols->tables[index].size_value);
                return &symbols->tables[index];
        } else {
                printf("value not found\n");
                exit(0);
                // return "not found";
        }
}
