#include "common.h"
#include "chunk.h"
#include "debug.h"

int main() {

    Chunk chunk; // TODO: what allocates this?
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, constant);

    writeChunk(&chunk, OP_RETURN);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
