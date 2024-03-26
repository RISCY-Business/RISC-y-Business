#include "JTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

jTypeExecutor* initialiseJTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    jTypeExecutor* executor = (jTypeExecutor*)malloc(sizeof(jTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyJTypeExecutor(jTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void executeJTypeInstruction(jTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE])
{
    short rd = toDecimal(Instruction, RD_START, RD_END, false);
    Bit immediateBits[IMMEDIATE_SIZE];

    for (int i = 0; i < IMMEDIATE_SIZE; ++i)
    {
        immediateBits[i] = Instruction[i];
    }

    short immediate = signExtend(immediateBits, IMMEDIATE_SIZE);
    Bit programCounterBits[REGISTER_SIZE];

    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        programCounterBits[i].value = ((*EXECUTOR->programCounter + 4) >> i) & 1;
    }

    setRegisterValue(&EXECUTOR->registerFile->registers[rd], programCounterBits);
}

// - - - - - - - - - - - - 

