#include <ctype.h>

#include "codeword_lookup.h"

int alphanumeric_lookup(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else if (isalpha(c)) {
        return toupper(c) - 'A' + 10;
    } else {
        switch (c) {
            case ' ':
                return 36;
            case '$':
                return 37;
            case '%':
                return 38;
            case '*':
                return 39;
            case '+':
                return 40;
            case '-':
                return 41;
            case '.':
                return 42;
            case '/':
                return 43;
            case ':':
                return 44;
        }
    }
    return -1;
}

int numeric_lookup(char c) {
    if (isdigit(c)) {
        return c - '0';
    }
    return -1;
}
