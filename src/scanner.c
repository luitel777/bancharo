#include "scanner.h"
#include <string.h>
TOKENS tokens;

char next_buf() {
        column++;
        char_pointer++;
        current_char = source_buffer[char_pointer];
        return current_char;
}
char prev_buf() {
        column--;
        char_pointer--;
        current_char = source_buffer[char_pointer];
        return current_char;
}

void set_buf(int32_t location) { current_char = source_buffer[location]; }

void skip_newline() {
        while (current_char == '\n' || current_char == '\t' ||
               current_char == '\b' || current_char == ' ') {
                if (current_char == '\n') {
                        column = 1;
                        lines++;
                }
                next_buf();
                skip_newline();
        }
}

int64_t ctoi64(char val) { return val - 48; }

bool is_digit() {
        if (current_char > 47 && current_char < 58) {
                return true;
        }
        return false;
}

bool is_opr() {
        if (tokens == ADD || tokens == SUB || tokens == DIV || tokens == MUL) {
                return true;
        }
        return false;
}

int64_t get_number() {
        int64_t value = 0;
        while (is_digit()) {
                value = value * 10 + (ctoi64(current_char));
                next_buf();
        }
        prev_buf();
        return value;
}

// keyword contains
// setq, defun, while, print
bool is_setq() {
        if (current_char == 's') {
                if (next_buf() == 'e') {
                        if (next_buf() == 't') {
                                if (next_buf() == 'q') {
                                        return true;
                                } else {
                                        prev_buf();
                                }
                        } else {
                                prev_buf();
                        }
                } else {
                        prev_buf();
                }
        } else {
        }
        return false;
}
// keyword contains
// setq, defun, while, print
bool is_print() {
        if (current_char == 'p') {
                if (next_buf() == 'r') {
                        if (next_buf() == 'i') {
                                if (next_buf() == 'n') {
                                        if (next_buf() == 't') {
                                                return true;
                                        } else {
                                                return false;
                                        }
                                } else {
                                        prev_buf();
                                }
                        } else {
                                prev_buf();
                        }
                } else {
                        prev_buf();
                }
        } else {
        }
        return false;
}

// keyword contains
// setq, defun, while, print
bool is_while() {
        if (current_char == 'w') {
                if (next_buf() == 'h') {
                        if (next_buf() == 'i') {
                                if (next_buf() == 'l') {
                                        if (next_buf() == 'e') {
                                                return true;
                                        } else {
                                                return false;
                                        }
                                } else {
                                        prev_buf();
                                }
                        } else {
                                prev_buf();
                        }
                } else {
                        prev_buf();
                }
        } else {
        }
        return false;
}

bool is_defun() {
        if (current_char == 'd') {
                if (next_buf() == 'e') {
                        if (next_buf() == 'f') {
                                if (next_buf() == 'u') {
                                        if (next_buf() == 'n') {
                                                return true;
                                        } else {
                                                return false;
                                        }
                                } else {
                                        prev_buf();
                                }
                        } else {
                                prev_buf();
                        }
                } else {
                        prev_buf();
                }
        } else {
        }
        return false;
}

bool is_keyword() {
        if (is_setq()) {
                return true;
        }
        return false;
}

char *give_identifier() {
        char *identifier = NULL;
        identifier = (char *)(malloc(sizeof(char) * 256));
        int index = 0;
        while (current_char != ' ' && current_char != ')' &&
               current_char != '(') {
                identifier[index] = current_char;
                index++;
                next_buf();
        }
        return identifier;
}

bool is_char() {
        if ((current_char > 64) && (current_char < 91))
                ;
        return true;
}

TOKENS identify_tokens() {
        skip_newline();
        if (current_char == '+') {
                tokens = ADD;
        } else if (current_char == '-') {
                tokens = SUB;
        } else if (current_char == '*') {
                tokens = MUL;
        } else if (current_char == '/') {
                tokens = DIV;
        } else if (current_char == '>') {
                tokens = GREATER;
        } else if (current_char == '<') {
                tokens = LESSER;
        } else if (is_digit()) {
                tokens = DIGIT;
                // int16_t value = get_number();
                // printf("digit found: \t\t %d\n", value);
        } else if (is_setq()) {
                tokens = SETQ;
                // printf("keyword found: \t\t setq\n");
        } else if (is_while()) {
                tokens = WHILE;
        } else if (is_print()) {
                tokens = PRINT;
        } else if (is_defun()) {
                tokens = DEFUN;
        } else if (current_char == '(') {
                tokens = S_L_PAREN;
        } else if (current_char == ')') {
                tokens = S_R_PAREN;
        } else if (current_char != '\0') {
                value = NULL;
                value = give_identifier();
                tokens = IDENT;
                prev_buf();
        } else {
                tokens = ERROR;
        }

        return tokens;
}