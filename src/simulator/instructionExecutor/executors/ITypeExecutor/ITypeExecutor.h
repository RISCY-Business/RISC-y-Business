#ifndef I_TYPE_EXECUTOR
#define I_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
#define RS1_START 15
#define RS1_END RS1_START + REGISTER_ADDRESS_SIZE
#define RD_START 7
#define RD_END RD_START + REGISTER_ADDRESS_SIZE
// - - - - - - - - -
#define IMMEDIATE_START 20
#define IMMEDIATE_SIZE 12
#define IMMEDIATE_END IMMEDIATE_START + IMMEDIATE_SIZE
// - - - - - - - - -
#define FUNCT3_START 12
#define FUNCT3_SIZE 3
#define FUNCT3_END FUNCT3_START + FUNCT3_SIZE
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
    unsigned short* programCounter;
} iTypeExecutor;

// - - - - - - - - -

iTypeExecutor* initialiseITypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* programCounter);

void destroyITypeExecutor(iTypeExecutor* EXECUTOR);

void executeITypeLWInstruction(iTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeITypeDefaultInstruction(iTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void executeITypeJumpInstruction(iTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void addi(Register* RD, Register* RS1, short IMMEDIATE);

void sltiu(Register* RD, Register* RS1, short IMMEDIATE);
// - - - - - - - -

#endif // I_TYPE_EXECUTOR
