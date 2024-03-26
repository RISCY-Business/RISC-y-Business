#ifndef S_TYPE_EXECUTOR
#define S_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
#define RS1_START 15
#define RS1_END RS1_START + REGISTER_ADDRESS_SIZE
#define RS2_START 20
#define RS2_END RS1_START + REGISTER_ADDRESS_SIZE
// - - - - - - - - -
#define FIRST_HALF_IMMEDIATE_SIZE 5
#define SECOND_HALF_IMMEDIATE_SIZE 7
#define FIRST_HALF_IMMEDIATE_START 0
#define FIRST_HALF_IMMEDIATE_END FIRST_HALF_IMMEDIATE_START + FIRST_HALF_IMMEDIATE_SIZE
#define SECOND_HALF_IMMEDIATE_START 5
#define SECOND_HALF_IMMEDIATE_END SECOND_HALF_IMMEDIATE_START + SECOND_HALF_IMMEDIATE_SIZE
// - - - - - - - - -
#define VIRTUAL_DATA_ADDRESS_START 65536
#define VIRTUAL_DATA_ADDRESS_END 131071
#define VIRTUAL_STACK_ADDRESS_START 256
#define VIRTUAL_STACK_ADDRESS_END 383
#define STACK_OFFSET 64
#define DATA_OFFSET 16384
#define SCALE_FACTOR 4
// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
} sTypeExecutor;

// - - - - - - - - -

sTypeExecutor* initialiseSTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE);

void destroySTypeExecutor(sTypeExecutor* EXECUTOR);

void executeSTypeInstruction(sTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // S_TYPE_EXECUTOR
