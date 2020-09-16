#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
    // set stack top to point to beginning of array.
    // don't need to clear unused cells because we just won't use them until after
    vm.stackTop = vm.stack;
    // we can do this because an array is just a pointer to the first element (I think)
}

void initVM() {
    resetStack();
}

void freeVM() {

}

void push(Value value) {
    // TODO why dereference and now arrow here?
    *vm.stackTop = value;
    vm.stackTop++; // point at index after top
}

Value pop() {
    /*
     * `stackTop` points at next unused space in the stack, so in order to return the
     * last element (i.e. the top) on the stack we decrement it and then return the
     * value that's there. We can then leave stackTop pointing at it since after the
     * `pop()` operation it is now the next unused space in the stack.
     */
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++) // read the byte currently pointed at by the ip and increment it (increment before execution)

// read next byte in bytecode, which is index of constant in const pool, and look it up
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for(;;) { // every turn through this loop, we will read and execute a single bytecode instruction
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {

#ifdef DEBUG_TRACE_EXECUTION
            // print the contents of the stack from bottom (first) to top (last) before disassembling the instruction
            printf("          ");
            for(Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[");
                printValue(*slot);
                printf("]");
            }
            printf("\n");

            // disassembleInstruction takes a byte offset so we need to convert ip back to a relative offset from the beginning of the bytecode
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }

        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk; // store chunk being executed in vm
    vm.ip = vm.chunk->code; // point to first byte of code in the chunk
    return run();
}
