#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < chunk->count; ) {
        // delegate increment of `offset` to `disassembleInstruction`
        // because different instructions will take up different sizes
        // in the array, so offset should point to beginning of next instruction
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1; // simple instructions are only one byte
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {

    // actual constant index value is next value in array after opcode
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);

    // bytecode only has index of constant so need to look it up from
    // constant pool
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    // constants are two bytes - one for opcode and one for index of constant
    return offset + 2; // next instruction is after index of constant
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset); // `%04d` is signed integer prepended with 4 zeros

    if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("  | "); // many lines result in a number of bytecode instructions,
        // so depict that visually with a pipe
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];
    switch(instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_ADD: // arithmetic _operators_ take operands but arithmetic _bytecode instructions_ do not
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}