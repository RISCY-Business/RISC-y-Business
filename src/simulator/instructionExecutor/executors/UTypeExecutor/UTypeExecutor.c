#include "UTypeExecutor.h"
#include <stdlib.h>
// - - - - - - - - - - - - - -

uTypeExecutor* initialiseUTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    uTypeExecutor* executor = (uTypeExecutor*)malloc(sizeof(uTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyUTypeExecutor(uTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void executeUType1Instruction(uTypeExecutor *EXECUTOR, Bit *Instruction)
{
    //JUST SOMEBODY: I dont understand the difference between the two functions
    //I will see it when debugging
    executeUType2Instruction(EXECUTOR, Instruction);
}

// - - - - - - - - - - - - -

void executeUType2Instruction(uTypeExecutor *EXECUTOR, Bit *Instruction)
{
    short rd = toDecimal(Instruction, RD_START, RD_END, false);
    short immediate = toDecimal(Instruction, IMMEDIATE_START, IMMEDIATE_END, true) << SHIFT_OFFSET;
    Bit immediateBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        immediateBits[i].value = (immediate >> i) & 1;
    }
    short answer = signExtend(immediateBits, REGISTER_SIZE) + *EXECUTOR->programCounter;
    Bit answerBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answerBits[i].value = (answer >> i) & 1;
    }
    setRegisterValue(&EXECUTOR->registerFile->registers[rd], answerBits);
}
