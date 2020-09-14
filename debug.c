#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for(int offset = 0; offset < chunk->count; ) {
        // delegate increment of `offset` to `disassembleInstruction`
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {

    // actual constant index value is next value in array after opcode
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);

    // bytecode only has index of constant so need to look it up from
    // constant pool
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    return offset + 2; // next instruction is after index of constant
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset); // `%04d` is signed integer prepended with 4 zeros

    uint8_t instruction = chunk->code[offset];
    switch(instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}