#ifndef REGISTERS_H
#define REGISTERS_H
#include "../../../include/bit/bit.h"
// - - - - - - - - - -

//JUST SOMEBODY: We will have 32 registers of 32 bits each
#define REGISTER_COUNT 32
#define REGISTER_SIZE 32
#define REGISTER_ADDRESS_SIZE 5

/*
JUST SOMEBODY: A register is just a 32 bit storage with an ABI name and a 5 bit address. Since an adress cannot be changed, it is a const array.
*/

typedef struct
{
    Bit bits[REGISTER_SIZE];
    Bit address[REGISTER_ADDRESS_SIZE];
    char* abi;
} Register;

/*
JUST SOMEBODY: A register file is just an array of registers. 
Register x3 is at index 3
*/

typedef struct
{
    Register registers[REGISTER_COUNT];
} RegisterFile;

/*
JUST SOMEBODY: Here is how init and deallocate will work: take a register file, and then initialise all bits in all registers to 0. We will use only 1 malloc to create all registers
free all registers.
Getting a register by its ABI is as simple as a map.
Also we can get the address of a register too.
*/
RegisterFile* initializeRegisters();

void deallocateRegisters(RegisterFile *REGISTER_FILE);

Register* getRegister(RegisterFile *REGISTER_FILE, const char* ABI);

Register* getRegisterByIndex(RegisterFile* REGISTER_FILE, char index);

const char* getABI(RegisterFile *REGISTER_FILE, unsigned int index);

const Bit* getAddress(RegisterFile *REGISTER_FILE, const char* ABI);

unsigned int hash(const char* abiName);

void setRegisterValue(Register *REGISTER, const Bit BITS[REGISTER_SIZE]);

void setBit(Register *REGISTER, unsigned int INDEX, const Bit *BIT);

void printRegister(const Register *REGISTER);

void printRegisterFile(const RegisterFile *REGISTER_FILE);

// - - - - - - - - - -
#endif // REGISTERS_H
