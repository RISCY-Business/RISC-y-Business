#ifndef EXECUTOR_MANAGER
#define EXECUTOR_MANAGER
#include "../../memory/memory.h"
#include "../executors/RTypeExecutor/RTypeExecutor.h"
#include "../executors/ITypeExecutor/ITypeExecutor.h"
#include "../executors/STypeExecutor/STypeExecutor.h"
#include "../executors/BTypeExecutor/BTypeExecutor.h"
#include "../executors/UTypeExecutor/UTypeExecutor.h"
#include "../executors/JTypeExecutor/JTypeExecutor.h"

// - - - - - - - - - - - - -

#define INSTRUCTION_SIZE 32

#define OPCODE_START 0
#define OPCODE_END 6

#define R_TYPE 51
// - - - - - -
#define I_TYPE_LW 3
#define I_TYPE_DEFAULT 19
#define I_TYPE_JUMP 103
// - - - - - -
#define S_TYPE 35
// - - - - - -
#define B_TYPE 99
// - - - - - -
#define U_TYPE_1 55
#define U_TYPE_2 23
// - - - - - -
#define J_TYPE 111
// - - - - - -
#define HALT 0
// - - - - - - - -

typedef struct
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
    rTypeExecutor* rTypeExecutor;
    iTypeExecutor* iTypeExecutor;
    sTypeExecutor* sTypeExecutor;
    bTypeExecutor* bTypeExecutor;
    uTypeExecutor* uTypeExecutor;
    jTypeExecutor* jTypeExecutor;
} ExecutorManager;

ExecutorManager* initializeExecutorManager(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER);

void findAndExecute(ExecutorManager* EXECUTION_MANAGER, Bit INSTRUCTION[INSTRUCTION_SIZE]);

void destroyExecutorManager(ExecutorManager* EXECUTION_MANAGER);

// - - - - - - - -

#endif // !EXECUTOR_MANAGER
