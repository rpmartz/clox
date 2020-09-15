#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;

    // instruction pointer (aka program counter) points to instruction about to be executed
    // NOT to the instruction being currently executed
    uint8_t* ip; // faster to dereference a pointer than look up an element in an array
    Value stack[STACK_MAX];
    Value* stackTop; // stack always points to first empty space in array so that in an empty stack it points at index 0
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();
#endif