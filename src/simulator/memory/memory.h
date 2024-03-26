#ifndef MEMORY_H
#define MEMORY_H
#include "../register/registers.h"
// - - - - - - - - - 

//JUST SOMEBODY: I am going to create one memory allocate for whole 512 bits, 256 for program, 128 each for stack and data
#define PROGRAM_MEMORY 64 //64 cells of 32 bits each. 256 bytes
#define STACK_MEMORY 32 //32 cells of 32 bits each. 128 bytes
#define DATA_MEMORY 32 //32 cells of 32 bits each. 128 bytes
#define MEMORY_SIZE STACK_MEMORY+PROGRAM_MEMORY+DATA_MEMORY //128 cells of 32 bits each. 512 bytes
#define MEMORY_CELL_SIZE 32 //32 bits
#define ADDRESS_SIZE 7 //32 bits
#define PROGRAM_ADDRESS_START 0 // 0x00000000
#define PROGRAM_ADDRESS_END PROGRAM_ADDRESS_START + PROGRAM_MEMORY // 0x000000FF
#define STACK_ADDRESS_START PROGRAM_ADDRESS_END // 0x00000100 
#define STACK_ADDRESS_END  STACK_ADDRESS_START + STACK_MEMORY// 0x0000017F
#define DATA_ADDRESS_START STACK_ADDRESS_END // 0x00100000
#define DATA_ADDRESS_END DATA_ADDRESS_START + DATA_MEMORY // 0x0010007F

/* 
JUST SOMEBODY: A memory block is just a 512 byte storage with 256 byte for program. 128 bytes for stack and 128 bytes for data . A memory cell is just a storage of 1 byte with an address
*/

typedef struct
{
    Bit address[ADDRESS_SIZE];
    Bit bits[MEMORY_CELL_SIZE];
} MemoryCell;

typedef struct
{
    MemoryCell programMemory[PROGRAM_MEMORY];
    MemoryCell stackMemory[STACK_MEMORY];
    MemoryCell dataMemory[DATA_MEMORY];
    Register* stackPointer;
} Memory;

/*
JUST SOMEBODY: Here is how the memory is going to be allocated. We will have only one malloc for the whole memory. 
Then we will have pointers to the program, stack and data memory. 
Deallocation will be done by freeing the whole memory.
*/


Memory* allocateMemory(Register* STACK_POINTER);

void deallocateMemory(Memory* MEMORY);

static bool isAddressInRange(const Bit ADDRESS[ADDRESS_SIZE], int start, int end);

int calculateMemoryIndex(const Bit ADDRESS[ADDRESS_SIZE]);

MemoryCell* getProgramMemory(Memory* MEMORY);

MemoryCell* getMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE]);

void printMemoryCell(const MemoryCell *MEMORYCELL);

//JUST_SOMEBODY: Handling stack memory- - - - - - - - -

MemoryCell* getStackMemory(Memory* MEMORY);

void printStackMemory(const Memory* MEMORY);

void decreaseStackPointer(Memory* MEMORY);

void increaseStackPointer(Memory* MEMORY);

void pushStackMemory(Memory* MEMORY, const Register* REGISTER);

Bit* popStackMemory(Memory* MEMORY);

//JUST_SOMEBODY: Handling data memory- - - - - - - - -

MemoryCell* getDataMemory(Memory* MEMORY);

void printDataMemory(const Memory* MEMORY);

void setDataMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE], const Bit VALUE[MEMORY_CELL_SIZE]);

void setDataMemoryCellByIndex(Memory* MEMORY, int INDEX, const Bit VALUE[MEMORY_CELL_SIZE]);

//JUST_SOMEBODY: Handling Program memory- - - - - - -

void loadBinaryToProgramMemory(Memory* MEMORY, const char* RELATIVE_FILE_PATH);

void printProgramMemory(const Memory* MEMORY);

// - - - - - - - - -

#endif // MEMORY_H

