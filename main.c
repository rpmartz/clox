#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {
    initVM();

    Chunk chunk; // TODO: what allocates this?
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 341);
    writeChunk(&chunk, constant, 341);
    writeChunk(&chunk, OP_NEGATE, 341);

    writeChunk(&chunk, OP_RETURN, 341);
    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}
