#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code; // wrapper around array of bytes
} Chunk; // this struct represents a dynamic array of bytes

void initChunk(Chunk* chunk);

#endif