#ifndef R_TYPE_EXECUTOR
#define R_TYPE_EXECUTOR
#include "../../../memory/memory.h"
// - - - - - - - - -

#define INSTRUCTION_SIZE 32
#define FUNCT3_SIZE 3
#define FUNCT7_SIZE 7
#define FUNCT3_START 12
#define FUNCT7_START 25
#define RD_START 7
#define RS1_START 15
#define RS2_START 20
#define FUNCT3_END FUNCT3_START + FUNCT3_SIZE
#define FUNCT7_END FUNCT7_START + FUNCT7_SIZE
#define RD_END RD_START + REGISTER_ADDRESS_SIZE
#define RS1_END RS1_START + REGISTER_ADDRESS_SIZE
#define RS2_END RS2_START + REGISTER_ADDRESS_SIZE


#define ADD_SUB 0
#define ADD 0
#define SUB 1
#define SLL 1
#define SLT 2
#define SLTU 3
#define XOR 4
#define SRL 5
#define OR 6
#define AND 7

#define SHIFT_LIMIT 5

// - - - - - - - - -

typedef struct  
{
    Memory* memoryManager;
    RegisterFile* registerFile;
} rTypeExecutor;

// - - - - - - - - -

rTypeExecutor* initialiseRTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE);

void destroyRTypeExecutor(rTypeExecutor* EXECUTOR);

void executeRTypeInstruction(rTypeExecutor* EXECUTOR, Bit Instruction[INSTRUCTION_SIZE]);

void add_sub(Register* RD, Register* RS1, Register* RS2, bool IS_SUB);

void slt(Register* RD, Register* RS1, Register* RS2, bool IS_SIGNED);

void bitwiseXor(Register* RD, Register* RS1, Register* RS2);

void bitwiseOr(Register* RD, Register* RS1, Register* RS2);

void bitwiseAnd(Register* RD, Register* RS1, Register* RS2);

void shiftBits(Register* RD, Register* RS1, Register* RS2, bool SHIFT_LEFT);


// - - - - - - - -

#endif // R_TYPE_EXECUTOR
