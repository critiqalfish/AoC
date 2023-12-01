#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int main (int argc, char * argv[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    long calibration = 0;

    fp = fopen("input.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        int first = -1;
        int last = -1;
        int full = 0;
        read = strcspn(line, "\n");

        #if DEBUG
        printf("%zu: ", read);
        #endif

        for (int i = 0; i < read; i++) {
            #if DEBUG
            printf("%c", line[i]);
            #endif
            
            if (line[i] > 47 && line[i] < 58) {
                if (first < 0) {
                    first = line[i] - '0';
                }
                last = atoi(&line[i]);
            }
        }

        full = first * 10 + last;
        calibration += full;

        #if DEBUG
        printf(":%d %d %d\n", first, last, full);
        #endif
    }

    #if DEBUG
    printf("\ncalibration: %ld\n", calibration);
    #endif

    fclose(fp);
    free(line);
    return 0;
}