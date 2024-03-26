#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "../register/registers.h"

typedef enum 
{
  R_TYPE,
  I_TYPE,
  S_TYPE,
  B_TYPE,
  U_TYPE,
  J_TYPE,
  COMMENT
} InstructionType;

typedef struct 
{
  char *name;
  InstructionType type;
  Bit bits[7];
} Opcode;

typedef struct 
{
  int number;
  Bit bits[12];
} Immediate;

typedef struct 
{
  char *name;
  bool isPresent;
} Label;

typedef struct 
{
  Opcode opcode;
  Register *registers;
  Label label;
  Immediate *immediates;
  unsigned int position;
  Bit funct3[3];
  Bit funct7[7];
    unsigned short elementCount[7];
} Instruction;

typedef struct 
{
    Instruction *instructions;
    unsigned int size;

} InputFile;

// - - - - - - - - - - -

char *readFile(const char *RELATIVE_FILE_PATH);

Instruction *assignInstruction(char *ASSEMBLY_CODE);

void writeFile(InputFile *INPUT);

#endif //  INSTRUCTIONS_H
