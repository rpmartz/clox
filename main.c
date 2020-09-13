#include "common.h"
#include "chunk.h"
#include "debug.h"

int main() {

    Chunk chunk; // TODO: what allocates this?
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
