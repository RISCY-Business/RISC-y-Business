#ifndef U_TYPE_EXECUTOR
#define U_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
#define IMMEDIATE_SIZE 20
#define IMMEDIATE_START 12
#define IMMEDIATE_END IMMEDIATE_START + IMMEDIATE_SIZE
#define RD_START 7
#define RD_END RD_START + REGISTER_ADDRESS_SIZE
#define SHIFT_OFFSET 12

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} uTypeExecutor;

// - - - - - - - - -

uTypeExecutor* initialiseUTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyUTypeExecutor(uTypeExecutor* EXECUTOR);

void executeUType1Instruction(uTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeUType2Instruction(uTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // U_TYPE_EXECUTOR
