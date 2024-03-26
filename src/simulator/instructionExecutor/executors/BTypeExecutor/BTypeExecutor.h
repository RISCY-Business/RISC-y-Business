#ifndef B_TYPE_EXECUTOR
#define B_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
// - - - - - - - - -
#define FIRST_HALF_IMMEDIATE_START 7
#define FIRST_HALF_IMMEDIATE_SIZE 5
#define FIRST_HALF_IMMEDIATE_END FIRST_HALF_IMMEDIATE_START + FIRST_HALF_IMMEDIATE_SIZE
// - - - - - - - - -
#define FUNCT3_START 12
#define FUNCT3_SIZE 3
#define FUNCT3_END FUNCT3_START + FUNCT3_SIZE
// - - - - - - - - -
#define RS1_START 15
#define RS1_END RS1_START + REGISTER_ADDRESS_SIZE
// - - - - - - - - -
#define RS2_START 20
#define RS2_END RS2_START + REGISTER_ADDRESS_SIZE
// - - - - - - - - -
#define SECOND_HALF_IMMEDIATE_START 25
#define SECOND_HALF_IMMEDIATE_SIZE 7
#define SECOND_HALF_IMMEDIATE_END SECOND_HALF_IMMEDIATE_START + SECOND_HALF_IMMEDIATE_SIZE
// - - - - - - - - -
#define BEQ 0
#define BNE 1
#define BLT 4
#define BGE 5
#define BLTU 6
#define BGEU 7
// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} bTypeExecutor;

// - - - - - - - - -

bTypeExecutor* initialiseBTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyBTypeExecutor(bTypeExecutor* EXECUTOR);

void executeBTypeInstruction(bTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void branch(bTypeExecutor* EXECUTOR, bool CONDITION, short IMMEDIATE);

// - - - - - - - -

#endif // B_TYPE_EXECUTOR
