#include <stdio.h>

#include "common.h"
#include "compiler.h"
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

// do-while is a preprocessor hack to allow a series of statements
// that can also end in a semicolon
#define BINARY_OP(op) \
    do {              \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while(false)

    for(;;) { // every turn through this loop, we will read and execute a single bytecode instruction
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

        uint8_t instruction;
        switch(instruction = READ_BYTE()) {

            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
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
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}
