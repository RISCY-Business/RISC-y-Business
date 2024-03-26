#include "simulator.h"
#include "instructionExecutor/executorManager/executorManager.h"
#include <stdio.h>
#include <stdlib.h>
// - - - - - - - - -

//Initialise and deinitialise functions

Simulator* initializeSimulator()
{
    //Allocate memory for the Simulator struct
    printf("Creating simulator\n");
    Simulator* simulator = (Simulator*) malloc(sizeof(Simulator));
    
    if (simulator == NULL)
    {
        perror("Error: Failed to allocate memory for Simulator\n");
        exit(EXIT_FAILURE);
    }
    
    //Initialize the register file
    simulator->registerFile = initializeRegisters();
    if (simulator->registerFile == NULL)
    {
        perror("Error: Failed to initialize Register File\n");
        free(simulator);
        exit(EXIT_FAILURE);
    }

    //Initialize the memory manager
    simulator->memoryManager = allocateMemory(getRegister(simulator->registerFile, "sp"));
    if (simulator->memoryManager == NULL)
    {
        perror("Error: Failed to initialize memory manager");
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }

    //Initialize the program counter
    unsigned short programCounter = 0; //define the program counter in the stack instead of the heap
    simulator->programCounter = &programCounter;
    if (simulator->programCounter == NULL)
    {
        perror("Error: Failed to initialize program counter");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }
    *simulator->programCounter = 0;
    printf("program counter created\n");

    simulator->executionManager = initializeExecutorManager(simulator->memoryManager, simulator->registerFile, simulator->programCounter);
    if (simulator->executionManager == NULL)
    {
        perror("Error: Failed to initialize executor manager");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
    }

    printf("Simulator created\n");
    return simulator;
}

// - - - - - - - - -

void loadProgram(Simulator *SIMULATOR, const char* BINARY_FILE_PATH)
{
    SIMULATOR->binaryFilePath = BINARY_FILE_PATH;
    printf("Loading program into memory\n");
    loadBinaryToProgramMemory(SIMULATOR->memoryManager, SIMULATOR->binaryFilePath);
}

// - - - - - - - - -

void deinitializeSimulator(Simulator *SIMULATOR)
{
    free(SIMULATOR->executionManager);
    free(SIMULATOR->memoryManager);
    free(SIMULATOR->registerFile);
    free(SIMULATOR);

    printf("Program successfully terminated");
    exit(EXIT_SUCCESS);
}

// - - - - - - - - - - -

//Print functions:

void printRegisters(const Simulator *SIMULATOR)
{
    printf("Register file for the Simulation %s\n", *SIMULATOR);
    printRegisterFile(SIMULATOR->registerFile);
}

// - - - - - - - - - - -

void printMemory(const Simulator *SIMULATOR)
{
    printf("Memory manager for the Simulation %s\n", *SIMULATOR);
    printProgramMemory(SIMULATOR->memoryManager);
    printStackMemory(SIMULATOR->memoryManager);
    printDataMemory(SIMULATOR->memoryManager);
}

// - - - - - - - - - - -

void runSimulation(Simulator *SIMULATOR)
{
    while (!(*SIMULATOR->programCounter >= PROGRAM_MEMORY))
    {
        Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
        findAndExecute(SIMULATOR->executionManager, instruction);
        printRegisters(SIMULATOR);
    }
    printMemory(SIMULATOR);
}

// - - - - - - - - - -

