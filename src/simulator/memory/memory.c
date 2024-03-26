#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// - - - - - - - - -

Memory* allocateMemory(Register* STACK_POINTER)
{
    //Allocate memory for the memory
    Memory* memory = (Memory*)malloc(sizeof(Memory));
    if (memory == NULL)
    {
        perror("Error allocating memory for memory\nOperation: initialising");
        exit(EXIT_FAILURE);
    }

    //Initialise all bits of all memory cells to 0 and give them their address
    for (int i = 0; i < PROGRAM_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->programMemory[i].bits[j].value = 0;
        }
        
        for (int k = ADDRESS_SIZE - 1; k >= 0; --k) 
        {
            memory->programMemory[i].address[k].value = ((i + PROGRAM_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    for (int i = 0; i < STACK_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->stackMemory[i].bits[j].value = 0;
        }
        for (int k = 0; k < ADDRESS_SIZE; ++k)
        {
            memory->stackMemory[i].address[k].value = ((i + STACK_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    for (int i = 0; i < DATA_MEMORY; ++i)
    {
        for (int j = 0; j < MEMORY_CELL_SIZE; ++j)
        {
            memory->dataMemory[i].bits[j].value = 0;
        }
        for (int k = 0; k < ADDRESS_SIZE; ++k)
        {
            memory->dataMemory[i].address[k].value = ((i + DATA_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        }
    }

    //Set the stackPointer and initialise to the address of the first cell in stack memory
    memory->stackPointer = STACK_POINTER;
    Bit stackPointerAddress[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE-ADDRESS_SIZE; ++i)
    {
        stackPointerAddress[i].value = 0;
    }
    for (int i = REGISTER_SIZE-ADDRESS_SIZE; i < REGISTER_SIZE; ++i)
    {
        stackPointerAddress[i].value = memory->stackMemory[0].address[i-(REGISTER_SIZE-ADDRESS_SIZE)].value;
    }
    setRegisterValue(memory->stackPointer, stackPointerAddress);


    return memory;
}

// - - - - - - - - -

void deallocateMemory(Memory* MEMORY)
{
    free(MEMORY);
}

// - - - - - - - - -

MemoryCell* getProgramMemory(Memory* MEMORY)
{
    return MEMORY->programMemory;
}

// - - - - - - - - - 

MemoryCell* getStackMemory(Memory* MEMORY)
{
    return MEMORY->stackMemory;
}

// - - - - - - - - -

MemoryCell* getDataMemory(Memory* MEMORY)
{
    return MEMORY->dataMemory;
}

// - - - - - - - - -

void printMemoryCell(const MemoryCell* MEMORYCELL)
{
    printf("Address: ");
    for (int i = 0; i < ADDRESS_SIZE; ++i)
    {
        printf("%d", MEMORYCELL->address[i].value);
    }
    printf(" , Value: ");
    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        printf("%d", MEMORYCELL->bits[i].value);
    }
}

// - - - - - - -

void printProgramMemory(const Memory* MEMORY)
{
    printf("\nProgram Memory:\n");
    for (int i = 0; i < PROGRAM_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->programMemory[i]);
        printf("\n");
    }
}

// - - - - - - - - 

void printStackMemory(const Memory* MEMORY)
{
    printf("\nStack Memory:\n");
    for (int i = 0; i < STACK_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->stackMemory[i]);
        printf("\n");
    }
}

// - - - - - - - - 

void printDataMemory(const Memory* MEMORY)
{
    printf("\nData Memory:\n");
    for (int i = 0; i < DATA_MEMORY; ++i)
    {
        printMemoryCell(&MEMORY->dataMemory[i]);
        printf("\n");
    }
}

// - - - - - - - -

void decreaseStackPointer(Memory* MEMORY)
{
    //JUST_SOMEBODY: Throw error on underflow;
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) <= STACK_ADDRESS_START)
    {
        perror("Stack Underflow");
        exit(EXIT_FAILURE);
    }

    decrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}

// - - - - - - - -

void increaseStackPointer(Memory* MEMORY)
{
    //JUST_SOMEBODY: Throw error on underflow;
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack Overflow! Very punny!");
        exit(EXIT_FAILURE);
    }

    incrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}

// - - - - - - - - -

static bool isAddressInRange(const Bit ADDRESS[ADDRESS_SIZE], int start, int end)
{
    for (int i = 0; i < ADDRESS_SIZE; ++i)
    {
        if (ADDRESS[i].value != ((start >> (ADDRESS_SIZE - 1 -i)) & 1))
        {
            return 0; //ADDRESS DOESNT MATCH
        }
    }

    return 1; //ADDRESS IS IN THE VALID RANGE
}

// - - - - - - - - - -

int calculateMemoryIndex(const Bit ADDRESS[ADDRESS_SIZE])
{
    //Just somebody: this function returns the index of the memory cell in the memory array of the specific memory type
    //So if the address is 0000000, the index points to the first cell in the program memory array and we will return 0;
    //So if the address is 1000001, the index points to the second cell in the stack memory array and we will return 1;

    int index = toDecimal(ADDRESS, 0, REGISTER_SIZE, false);
    if (index >= PROGRAM_MEMORY)
    {
        index = index % ADDRESS_SIZE;
    }
   
    return index - 1; //Because indexing starts at 0;
}

// - - - - - - - - - -

MemoryCell* getMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE])
{
    if (isAddressInRange(ADDRESS, PROGRAM_ADDRESS_START, PROGRAM_ADDRESS_END))
    {
        return &MEMORY->programMemory[calculateMemoryIndex(ADDRESS)];
    }
    if (isAddressInRange(ADDRESS, STACK_ADDRESS_START, STACK_ADDRESS_END))
    {
        return &MEMORY->stackMemory[calculateMemoryIndex(ADDRESS)];
    } 
    if (isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        return &MEMORY->dataMemory[calculateMemoryIndex(ADDRESS)];
    }

    return NULL;
}

// - - - - - - - - - -

void pushStackMemory(Memory* MEMORY, const Register* REGISTER)
{
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack Overflow! Very punny");
        exit(EXIT_FAILURE);
    }

    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);

//    int index = toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) % STACK_MEMORY;
    int index = calculateMemoryIndex(MEMORY->stackPointer->bits);
    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        MEMORY->stackMemory[index].bits[i].value = REGISTER->bits[i].value;
    }

    increaseStackPointer(MEMORY);
}

// - - - - - - - - -

Bit* popStackMemory(Memory* MEMORY)
{
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) <= STACK_ADDRESS_START)
    {
        perror("Stack Underflow");
        exit(EXIT_FAILURE);
    }

    decreaseStackPointer(MEMORY);
    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);
    //Reset the top of the stack memory to 0
    //int index = toDecimal(MEMORY->stackPointer->bits, REGISTER_SIZE, false) % 32;
    int index = calculateMemoryIndex(MEMORY->stackPointer->bits);
    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        MEMORY->stackMemory[index].bits[i].value = 0;
    }
    return stackTopCell->bits;
}

// - - - - - - - - -

void setDataMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE], const Bit* VALUE)
{
    if (!isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        perror("Invalid data address");
        exit(EXIT_FAILURE);
    }

    MemoryCell* dataMemoryCell = getMemoryCell(MEMORY, ADDRESS);

    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        dataMemoryCell->bits[i].value = VALUE[i].value;
    }
}

// - - - - - - - - -

void loadBinaryToProgramMemory(Memory* MEMORY, const char* RELATIVE_FILE_PATH)
{
    FILE* file = fopen(RELATIVE_FILE_PATH, "r");

    if (file == NULL)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[MEMORY_CELL_SIZE + 1]; //JUST SOMEBODY: plus one for the \n character.

    //JUST SOMEBODY: Reading each line and storing it in the programMemory for the simulator to execute

    int i = 0; // Initialize i outside the loop
    while (fgets(line, sizeof(line), file) != NULL && i < PROGRAM_MEMORY) // Stop when end of file is reached or PROGRAM_MEMORY lines are read
    {
        
        if (strlen(line) <= 1) // Check if the line is too short
        {
            continue;
        }

        for (int j = 0; j < MEMORY_CELL_SIZE && line[j] != '\n'; ++j) // Avoid processing newline characters
        {
            switch(line[j])
            {
                case '0':
                    MEMORY->programMemory[i].bits[j].value = 0;
                    break;
                case '1':
                    MEMORY->programMemory[i].bits[j].value = 1;
                    break;
                default:
                    printf("Encountered a non-binary character  '%c' while reading the file\n", line[j]);
                    perror("\n");
                    exit(EXIT_FAILURE);
            }
        }
        i++; // Increment i only when a line is successfully read and stored
    }

    fclose(file);
    printf("Successfully read and closed file\n");
}

// - - - - - - - - - - - - - - - - - - - - - -

void setDataMemoryCellByIndex(Memory *MEMORY, int INDEX, const Bit *VALUE)
{
    if (INDEX < 0 || INDEX >= DATA_MEMORY)
    {
        perror("Invalid data memory index\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        MEMORY->dataMemory[INDEX].bits[i].value = VALUE[i].value;
    }
}
