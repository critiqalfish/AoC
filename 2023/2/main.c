#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int main (int argc, char * argv[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int idsum = 0;

    fp = fopen("input.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        read = strcspn(line, "\n");
        int gameid = atoi(&line[5]);
        int impossible = 0;
        int i;

        if (gameid < 10) i = 8;
        else if (gameid < 100) i = 9;
        else i = 10;

        while (i < read) {
            int temp = atoi(&line[i]);
            if (temp < 10) i += 2;
            else i += 3;

            if (line[i] == 'r') {
                if (temp > 12) impossible++;
                i += 3;
            }
            else if (line[i] == 'g') {
                if (temp > 13) impossible++;
                i += 5;
            }
            else if (line[i] == 'b') {
                if (temp > 14) impossible++;
                i += 4;
            }

            i += 2;
        }

        if (!impossible) idsum += gameid;

        #if DEBUG
        printf("%d - %s", impossible, line);
        #endif
    }

    #if DEBUG
    printf("\n\nidsum: %d\n", idsum);
    #endif

    fclose(fp);
    free(line);
    return 0;
}