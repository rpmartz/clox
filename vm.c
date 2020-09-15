#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
    // set stack top to point to beginning of array
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++) // read the byte currently pointed at by the ip and increment it (increment before execution)

// read next byte in bytecode, which is index of constant in const pool, and look it up
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for(;;) { // every turn through this loop, we will read and execute a single bytecode instruction
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {

#ifdef DEBUG_TRACE_EXECUTION
            // disassembleInstruction takes a byte offset so we need to convert ip back to a relative offset from the beginning of the bytecode
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN: {
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
