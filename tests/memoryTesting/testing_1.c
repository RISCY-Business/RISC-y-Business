#include "../../src/simulator/memory/memory.h"
#include <stdio.h>

int main() {
    // Allocate memory
    Register stackPointer;
    Memory* memory = allocateMemory(&stackPointer);

    // Initialize a test register
    Register testRegister;
    Bit testBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        testBits[i].value = i % 2;  // Alternating 0s and 1s
    }
    setRegisterValue(&testRegister, testBits);
    printf("Test Register:\n");
    printRegister(&testRegister);

    // Test program memory access
    MemoryCell* programMemory = getProgramMemory(memory);
    printProgramMemory(memory);

    //Test ability to affect memory
    int index = calculateMemoryIndex(memory->stackMemory[16].address);
    printf("Index: %d\n", index);
    memory->stackMemory[0].bits[0].value = 1;

    // Test stack memory operations
    printf("Stack Pointer:\n");
    printRegister(memory->stackPointer);
    printStackMemory(memory);
    printf("\n");
    pushStackMemory(memory, &testRegister);

    pushStackMemory(memory, &testRegister);
    pushStackMemory(memory, &testRegister);

    printf("After 3 Push:\n");
    printStackMemory(memory);
    printRegister(memory->stackPointer);
    Bit* poppedBits = popStackMemory(memory);
    printf("After Pop:\n");
    printStackMemory(memory);
    printRegister(memory->stackPointer);

    //After 2 more pops
    poppedBits = popStackMemory(memory);
    poppedBits = popStackMemory(memory);
    printf("After 2 more Pops:\n");
    printStackMemory(memory);
    // Test data memory access
    MemoryCell* dataMemory = getDataMemory(memory);
    printDataMemory(memory);

    // Deallocate memory
    deallocateMemory(memory);

    return 0;
}
