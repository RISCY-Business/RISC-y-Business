#include "STypeExecutor.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - - - - - - -

sTypeExecutor* initialiseSTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE)
{
    sTypeExecutor* executor = (sTypeExecutor*)malloc(sizeof(sTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    return executor;
}

// - - - - - - - - - - - - -

void destroySTypeExecutor(sTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void executeSTypeInstruction(sTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE])
{
    unsigned char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    unsigned char rs2 = toDecimal(Instruction, RS2_START, RS2_END, false);
    short firstHalfImmediate = toDecimal(Instruction, FIRST_HALF_IMMEDIATE_START, FIRST_HALF_IMMEDIATE_END, true);
    short secondHalfImmediate = toDecimal(Instruction, SECOND_HALF_IMMEDIATE_START, SECOND_HALF_IMMEDIATE_END, true);
    short immediate = (secondHalfImmediate << FIRST_HALF_IMMEDIATE_SIZE) | firstHalfImmediate;

    int address = toDecimal(Instruction, RS2_START, RS2_END, true) + immediate / SCALE_FACTOR; // I am allowing it to be negative but throwing an error if it is negative

    if (address >= VIRTUAL_STACK_ADDRESS_START && address <= VIRTUAL_STACK_ADDRESS_END)
    {
        address -= STACK_OFFSET;
        for (int i = 0; i < REGISTER_SIZE; ++i)
        {
            EXECUTOR->memoryManager->stackMemory[address].bits[i].value = EXECUTOR->registerFile->registers[rs2].bits[i].value;
        }
        return;
    }

    if (address >= VIRTUAL_DATA_ADDRESS_START && address <= VIRTUAL_DATA_ADDRESS_END)
    {
        address -= DATA_OFFSET;
        setDataMemoryCellByIndex(EXECUTOR->memoryManager, address, EXECUTOR->registerFile->registers[rs2].bits);
        return;
    }

    perror("Invalid memory access\n");
    exit(EXIT_FAILURE);
}

// - - - - - - - - - - - - -
