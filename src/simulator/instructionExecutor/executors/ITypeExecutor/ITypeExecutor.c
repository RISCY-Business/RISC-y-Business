#include "ITypeExecutor.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - - - - - - -

iTypeExecutor* initialiseITypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    iTypeExecutor* executor = (iTypeExecutor*)malloc(sizeof(iTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

// - - - - - - - - - - - - -

void destroyITypeExecutor(iTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

// - - - - - - - - - - - - -

void addi(Register *RD, Register *RS1, short IMMEDIATE)
{
    short rs1 = signExtend(RS1->bits, REGISTER_SIZE);
    short rd = toDecimal(RD->bits, 0, REGISTER_SIZE, false);
    short answer = rs1 + IMMEDIATE;
    //Throw an error if the sp register becomes negative or overflows
    if (answer < 256 && (rd == 2 || rd == 3 || rd == 4))
    {
        perror("Stack pointer and related registers cannot be underflowed\n");
        exit(EXIT_FAILURE);
    }
    //Since the address assumed by the assembler for any address increases by 4, but our implementation increases by 1, we need to divide the answer by 4
    if (answer > 383 && (rd == 2 || rd == 3 || rd == 4))
    {
        perror("Stack pointer and related registers cannot be overflowed\n");
        exit(EXIT_FAILURE);
    }
    if (rd == 2 || rd == 3 || rd == 4)
    {
        answer /= 4;
    }
    Bit answerBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        answerBits[i].value = (answer >> i) & 1;
    }
    setRegisterValue(RD, answerBits);
}

// - - - - - - - - - - - - -

void sltiu(Register *RD, Register *RS1, short IMMEDIATE)
{
    short rs1 = toDecimal(RS1->bits, 0, REGISTER_SIZE, false);
    bool answer = rs1 < IMMEDIATE;
    Bit answerBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE - 1; ++i)
    {
        answerBits[i].value = 0;
    }
    answerBits[REGISTER_SIZE - 1].value = answer;
    setRegisterValue(RD, answerBits);
}

// - - - - - - - - - - - - -

void executeITypeJumpInstruction(iTypeExecutor *EXECUTOR, Bit *Instruction)
{
    unsigned char rd = toDecimal(Instruction, RD_START, RD_END, false);
    unsigned char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    Bit* immediateBits;
    for (int i = 0; i < IMMEDIATE_SIZE; ++i)
    {
        immediateBits[i].value = Instruction[i + IMMEDIATE_START].value;
    }
    short immediate = signExtend(immediateBits, IMMEDIATE_SIZE);
    int address = (toDecimal(getRegisterByIndex(EXECUTOR->registerFile, rs1)->bits, 0, REGISTER_SIZE, true) + immediate); 
    Bit* currentAddressBits;
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        currentAddressBits[i].value = (*EXECUTOR->programCounter >> i) & 1;
    }
    setRegisterValue(getRegisterByIndex(EXECUTOR->registerFile, rd), currentAddressBits);
    *EXECUTOR->programCounter = address;
}

// - - - - - - - - - - - - -

void executeITypeLWInstruction(iTypeExecutor *EXECUTOR, Bit *Instruction)
{
    //Same as the S type instruction, but the immediate is signed
    unsigned char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    unsigned char rd = toDecimal(Instruction, RD_START, RD_END, false);
    Bit* immediateBits;
    for (int i = 0; i < IMMEDIATE_SIZE; ++i)
    {
        immediateBits[i].value = Instruction[i + IMMEDIATE_START].value;
    }
    short immediate = signExtend(immediateBits, IMMEDIATE_SIZE);
    int address = toDecimal(Instruction, RS1_START, RS1_END, true) + immediate / SCALE_FACTOR; // I am allowing it to be negative but throwing an error if it is negative

    if (address >= VIRTUAL_STACK_ADDRESS_START && address <= VIRTUAL_STACK_ADDRESS_END)
    {
        address -= STACK_OFFSET; 
        setRegisterValue(getRegisterByIndex(EXECUTOR->registerFile, rd), EXECUTOR->memoryManager->stackMemory[address].bits);
        return;
    }

    if (address >= VIRTUAL_DATA_ADDRESS_START && address <= VIRTUAL_DATA_ADDRESS_END)
    {
        address -= DATA_OFFSET;
        setRegisterValue(getRegisterByIndex(EXECUTOR->registerFile, rd), EXECUTOR->memoryManager->dataMemory[address].bits);
        return;
    }

    perror("Invalid memory access\n");
    exit(EXIT_FAILURE);
}

// - - - - - - - - - - - - -

void executeITypeDefaultInstruction(iTypeExecutor *EXECUTOR, Bit *Instruction)
{
    char funct3 = toDecimal(Instruction, FUNCT3_START, FUNCT3_END, false);
    char rd = toDecimal(Instruction, RD_START, RD_END, false);
    char rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    short immediate = toDecimal(Instruction, IMMEDIATE_START, IMMEDIATE_END, false);
    Bit* immediateBits;
    for (int i = 0; i < IMMEDIATE_SIZE; ++i)
    {
        immediateBits[i].value = Instruction[i + IMMEDIATE_START].value;
    }
    short immediateSigned = signExtend(immediateBits, IMMEDIATE_SIZE);
    switch(funct3)
    {
        case 0:
            addi(&EXECUTOR->registerFile->registers[rd], &EXECUTOR->registerFile->registers[rs1], immediateSigned);
            break;

        case 1:
            sltiu(getRegisterByIndex(EXECUTOR->registerFile, rd), getRegisterByIndex(EXECUTOR->registerFile, rs1), immediate);
            break;
    }
}

// - - - - - - - - - - - - -

