#include "common.h"
#include "vm.h"

VM vm;

void initVM() {

}

void freeVM() {

}

InterpretResult interprest(Chunk* chunk) {
    vm.chunk = chunk; // store chunk being executed in vm
    vm.ip = vm.chunk->code; // point to first byte of code in the chunk
    return run()l
}
