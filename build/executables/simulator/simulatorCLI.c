//Make a simple main function that imports the simulator and asks the user for file path as input and then runs the simulator with the given file path.

#include <stdio.h>
#include "../../../src/simulator/simulator.h"

int main() {
    char file_path[100];
    printf("Enter the file path: ");
    scanf("%s", file_path);
    Simulator* simulator = initializeSimulator();
    loadProgram(simulator, file_path);
    runSimulation(simulator);
    return 0;
}
