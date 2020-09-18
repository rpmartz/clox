#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    // first phase of compilation is scanning
    initScanner(source);

    // temporary code for driving the scanner
    int line = -1;
    for(;;) {
        Token token = scanToken();
        if(token.line != line) {
            // print line number
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }

        // print numeric token type and the token
        // %.*s allows variable length tokens
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF) {
            break;
        }
    }
}