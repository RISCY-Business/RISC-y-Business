#include "instructions.h"
#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile(InputFile* INPUT)
{
    FILE* file = fopen("output.txt", "w");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", "output.txt");
        return;
    }

    for (unsigned int i = 0; i < INPUT->size; ++i)
    {
        Instruction *currentInstruction = &INPUT->instructions[i];
        //Make a string that will be added to the file. It is 32 characters long.
        char string[32];
        for (int i = 0; i < 7; ++i)
        {
            string[i] = currentInstruction->opcode.bits[i].value + '0';
        }


        
    }
}

int main()
{
    FILE* file = fopen("output.txt", "w");
    if (!file)
    {
        printf("Error: Could not open file %s\n", "output.txt");
        return 1;
    }
    fprintf(file, "Hello, World!\n");
    fclose(file);
    return 0;
}
