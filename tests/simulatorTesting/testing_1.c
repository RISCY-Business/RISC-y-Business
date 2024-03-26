#include "../../src/simulator/simulator.h"

int main()
{
    Simulator* a = initializeSimulator("testFile.txt");

    printProgramMemory(a->memoryManager);// This shouldnt say ready to execute
}
