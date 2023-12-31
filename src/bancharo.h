#ifndef __BANCHARO_MAIN__H__
#define __BANCHARO_MAIN__H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char current_char;
extern char source_buffer[429496];
extern int32_t char_pointer;
extern int32_t lines;
extern int32_t column;
extern char *value;

// copies file content to local buffer
// this is memory efficient since we do
// not have to rely of syscalls on every
// characters
void copy_buffer(char *file);
#endif
