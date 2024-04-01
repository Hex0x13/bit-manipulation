#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLAG_LENGTH_LIMIT 8


int bit_set(int n, int pos) {
    int mask = 1 << pos;
    return n | mask;
}

int bit_clear(int n, int pos) {
    int mask = ~(1 << pos);
    return n & mask;
}

int bit_toggle(int n, int pos) {
    int mask = 1 << pos;
    return n ^ mask;
}

int is_bit_set(int n, int pos) {
    int mask = 1 << pos;
    return  n & mask;
}

static char * to_bit_repr(int *src) {
    if (src == NULL){
        return NULL;
    }

    static char dest[37];
    char *ptr = (char *)src;
    int srcSize = 4;
    int c = 0;

    for (int i = srcSize - 1; i > -1; --i){
        char byte = *(ptr + i);
        for (int j = 7; j > -1; --j) {
            if ((byte >> j) & 1) {
                dest[c] = '1';
            } else {
                dest[c] = '0';
            }
            ++c;
        }
        dest[c] = ' ';
        ++c;
    }

    dest[36] = '\0';
    return dest;
}

void printErr(char *arg) {
    fprintf(stderr, "Usage: %s [flags] [number] [position]\n\n", arg);
    fprintf(stderr,
            "-s, set = set the particular bit in an integer to 1\n"
            "-c, clear = set the particular bit in an integer to 0\n"
            "-t, toggle = toggle the particular bit in an integer to 0 if bit == 1 else 1\n"
            "-?s, check = check the particular bit is set\n"
    );
}

long strtol_s(char *str) {
    char *endptr;
    long n = strtol(str, &endptr, 10);
    if ((errno == ERANGE && (n == LONG_MIN || n == LONG_MAX)) || (errno != 0 && n == 0)) {
        perror("strtol error");
        exit(1);
    }
    if (endptr == str || *endptr != '\0') {
        fprintf(stderr, "Input contains non-numeric characters\n");
        exit(1);
    }
    return  n;
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        char *flag = argv[1];
        int result;
        long n = strtol_s(argv[2]);
        long pos = strtol_s(argv[3]);


        if (strncmp(flag, "set", FLAG_LENGTH_LIMIT) == 0 || strncmp(flag, "-s", FLAG_LENGTH_LIMIT) == 0) {
            result = bit_set(n, pos);
        } else if (strncmp(flag, "clear", FLAG_LENGTH_LIMIT) == 0 || strncmp(flag, "-c", FLAG_LENGTH_LIMIT) == 0) {
            result = bit_clear(n, pos);
        } else if (strncmp(flag, "toggle", FLAG_LENGTH_LIMIT) == 0 || strncmp(flag, "-t", FLAG_LENGTH_LIMIT) == 0) {
            result = bit_toggle(n, pos);
        } else if (strncmp(flag, "check", FLAG_LENGTH_LIMIT) == 0 || strncmp(flag, "-?s", FLAG_LENGTH_LIMIT) == 0) {
            if (is_bit_set(n, pos)) {
                printf("Result: true\n");
            } else {
                printf("Result: false\n");
            }
            return 0;
        } else {
            printErr(argv[0]);
            return 1;
        }

        printf("base02: %s\n", to_bit_repr(&result));
        printf("base08: %#o\n", result);
        printf("base10: %d\n", result);
        printf("base16: %#x\n", result);
    } else {
        printErr(argv[0]);
        return 1;
    }
    return 0;
}
