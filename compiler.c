#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    // first phase of compilation is scanning
    initScanner(source);
}