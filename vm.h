#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;

    // instruction pointer (aka program counter) points to instruction about to be executed
    // NOT to the instruction being currently executed
    uint8_t* ip; // faster to dereference a pointer than look up an element in an array
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
#endif