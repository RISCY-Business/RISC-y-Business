#ifndef J_TYPE_EXECUTOR
#define J_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
// - - - - - - - - -
#define RD_START 7
#define RD_END RD_START + REGISTER_ADDRESS_SIZE
// - - - - - - - - -
#define IMMEDIATE_START 12
#define IMMEDIATE_SIZE 20
#define IMMEDIATE_END IMMEDIATE_START + IMMEDIATE_SIZE
// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
} jTypeExecutor;

// - - - - - - - - -

jTypeExecutor* initialiseJTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyJTypeExecutor(jTypeExecutor* EXECUTOR);

void executeJTypeInstruction(jTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

// - - - - - - - -

#endif // J_TYPE_EXECUTOR
