// This code could be used as a template for your utf8.c, but it's not required.

#include <stdint.h>
#include <stdio.h>
#include "utf8.h"

void decode_utf8_template(const char* s) {
    size_t i = 0;
    while (s[i] != '\0') {
        if (0) {
            // the single-byte case
            // ...
            i += 1;
        } else if (0) {
            // the two-byte case
            // ...
            i += 2;
        } else if (0) {
            // the three-byte case
            // ...
            i += 3;
        } else if (0) {
            // the four-byte case
            // ...
            i += 4;
        } else {
            printf("<li>Unknown byte, 0x%02hhx</li>\n", s[i]);
            i++;
        }
    }
}
