#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

struct stringArray {
    char ** strings;
    int used;
    int size;
};

int main (int argc, char * argv[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int partsum = 0;
    struct stringArray lines;

    lines.strings = (char **) malloc(32 * sizeof(char *));
    lines.used = 0;
    lines.size = 32;

    fp = fopen("input.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        read = strcspn(line, "\n");
        
        if (lines.used == lines.size) {
            lines.strings = (char **) realloc(lines.strings, (lines.used + 32) * sizeof(char *));
            lines.size += 32;
        }

        lines.strings[lines.used] = (char *) malloc(read + 1);
        strncpy(lines.strings[lines.used], line, read);
        lines.used++;

        #if DEBUG
        printf("%s\n", lines.strings[lines.used - 1]);
        #endif
    }

    for (int l = 0; l < lines.used; l++) {
        for (int c = 0; c < strlen(lines.strings[l]); c++) {
            if (lines.strings[l][c] >= '0' && lines.strings[l][c] <= '9') {
                int num = atoi(lines.strings[l] + c);
                
                int numlen;
                if (num < 10) numlen = 1;
                else if (num < 100) numlen = 2;
                else numlen = 3;

                for (int ll = l - 1; ll <= l + 1; ll++) {
                    for (int cc = c - 1; cc <= c + numlen; cc++) {
                        if (ll >= 0 && cc >= 0 && ll < lines.used && cc < strlen(lines.strings[l])) {
                            if(lines.strings[ll][cc] != '.' && (lines.strings[ll][cc] < '0' || lines.strings[ll][cc] > '9')) {
                                partsum += num;
                            }
                        }
                    }
                }

                c += numlen;
            }
        }
    }

    #if DEBUG
    printf("\n\npartsum: %d\n", partsum);
    #endif

    fclose(fp);
    free(line);
    free(lines.strings);
    return 0;
}