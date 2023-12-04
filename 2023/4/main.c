#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

struct intArray {
    int * numbers;
    int used;
    int size;
};

int main (int argc, char * argv[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int luckysum = 0;

    fp = fopen("input.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        read = strcspn(line, "\n");
        int c = 5;
        int card;
        int cardlen;

        if (line[c] == ' ') c++;
        if (line[c] == ' ') c++;
        card = atoi(&line[c]);

        if (card < 10) cardlen = 1;
        else if (card < 100) cardlen = 2;
        else cardlen = 3;

        c += cardlen + 2;

        struct intArray winning;
        struct intArray numbers;
        winning.numbers = (int *) malloc(16 * sizeof(int));
        numbers.numbers = (int *) malloc(16 * sizeof(int));
        winning.size = 16;
        numbers.size = 16;
        winning.used = 0;
        numbers.used = 0;

        while (line[c] != '|') {
            if (line[c] == ' ') c++;

            int w = atoi(&line[c]);

            int wlen;
            if (w < 10) wlen = 1;
            else wlen = 2;

            if (winning.used == winning.size) {
                winning.numbers = (int *) realloc(winning.numbers, (winning.size + 16) * sizeof(int));
                winning.size += 16;
            }

            winning.numbers[winning.used] = w;
            winning.used++;

            c += wlen + 1;
        }

        c += 2;

        while (c < read) {
            if (line[c] == ' ') c++;
            
            int n = atoi(&line[c]);

            int nlen;
            if (n < 10) nlen = 1;
            else nlen = 2;

            if (numbers.used == numbers.size) {
                numbers.numbers = (int *) realloc(numbers.numbers, (numbers.size + 16) * sizeof(int));
                numbers.size += 16;
            }

            numbers.numbers[numbers.used] = n;
            numbers.used++;

            c += nlen + 1;
        }

        float l = 0.5;

        for (int wi = 0; wi < winning.used; wi++) {
            for (int ni = 0; ni < numbers.used; ni++) {
                if (winning.numbers[wi] == numbers.numbers[ni]) l *= 2;
            }
        }

        if (l == 0.5) l = 0;
        #if DEBUG
        printf("%f: %s", l, line);
        #endif
        luckysum += l;
    }

    #if DEBUG
    printf("\n\nluckysum: %d\n", luckysum);
    #endif

    fclose(fp);
    return 0;
}