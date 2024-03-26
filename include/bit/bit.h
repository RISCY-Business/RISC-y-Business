#ifndef BIT_H
#define BIT_H
#include <stdbool.h>
// - - - - - - - - - -

#define BIT_ARRAY_SIZE 32;
/*
JUST SOMEBODY: This is how we will define a bit: a struct with just a boolean value of size 1 
Here is how we can use it:
int main()
{
    Bit myBit;
    myBit.value = 0; //Reset the bit
    myBit.value = 1; //Set the bit
}

If you give more than 1 as a value, the bit is considered set.
*/

typedef struct 
{
    bool value : 1;
} Bit;

Bit* makeBit(bool VALUE);

Bit* createBitArray(unsigned char SIZE);

Bit AND(const Bit* BIT_1, const Bit* BIT_2);

Bit OR(const Bit* BIT_1, const Bit* BIT_2);

Bit XOR(const Bit* BIT_1, const Bit* BIT_2);

Bit NAND(const Bit* BIT_1, const Bit* BIT_2);

Bit NOR(const Bit* BIT_1, const Bit* BIT_2);

Bit NOT(const Bit* BIT);

Bit* bitwiseOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE);

Bit* bitwiseXOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE);

Bit* bitwiseNOT(const Bit* BIT_ARRAY, unsigned char SIZE);

Bit* bitwiseAND(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE);

void incrementBitArray(Bit* BIT_ARRAY, unsigned char SIZE);

void decrementBitArray(Bit* BIT_ARRAY, unsigned char SIZE);

Bit* ADD(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE); 

Bit* SUB(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE); 

Bit* MUL(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE); 

Bit* toUnsignedBitArray(int decimal, unsigned char SIZE);

Bit* toSignedBitArray(int decimal, unsigned char SIZE);

int toDecimal(const Bit* BIT_ARRAY, unsigned char ARRAY_START, unsigned char ARRAY_END, bool IS_SIGNED);

short signExtend(const Bit* BIT_ARRAY, unsigned char SIZE);

// - - - - - - - - - - 
#endif //BIT_H
