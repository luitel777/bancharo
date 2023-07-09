#include "bancharo.h"
#include "parser.h"

char current_char = 0;
char source_buffer[429496] = {};
int32_t char_pointer = 0;
int32_t lines = 1;
int32_t column = 1;

int main(int argc, char *argv[]) {
        copy_buffer(argv[1]);

        current_char = source_buffer[char_pointer];

        // we make seconday node and primary node to fill our tree called p_tree
        // data comes in s_node p_node joins s_node to its leftmost side
        // so leftmost side is new instruction. This depends obviously
        AST_NODE *s_node = malloc(sizeof(AST_NODE));
        AST_NODE *p_node = malloc(sizeof(AST_NODE));
        AST_NODE **p_tree = malloc(sizeof(AST_NODE));
        (*p_tree) = p_node;

        while (current_char != '\0') {
                if ((p_node) == NULL) {
                        break;
                }
                while ((p_node)->left != NULL) {
                        (p_node) = (p_node)->left;
                }
                s_node = *parse_syntax();
                (p_node)->left = (s_node);
        }

        (*p_tree) = (*p_tree)->left;
        printf("finished creating nodes\n");

        print_tree(p_tree);

        free(s_node);
        free(p_node);
        free(p_tree);
}

void copy_buffer(char *file) {
        FILE *source_cood = fopen(file, "r");
        if (!source_cood) {
                fprintf(stderr, "error: cannot open file\n");
                exit(0);
        }
        while (fread(source_buffer, 107374, 4, source_cood) > 0)
                ;
}
