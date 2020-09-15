#include <stdio.h>

#include "common.h"
#include "vm.h"

VM vm;

void initVM() {

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