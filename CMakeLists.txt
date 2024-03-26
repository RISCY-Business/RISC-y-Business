cmake_minimum_required(VERSION 3.0)
project(RISC_V_Simulator)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

# Add include directories
include_directories(include)

# Add source files
set(SOURCE_FILES
    build/executables/simulator/simulatorCLI.c
    include/bit/bit.c
    src/simulator/simulator.c
    src/simulator/register/registers.c
    src/simulator/memory/memory.c
    src/simulator/instructionExecutor/executorManager/executorManager.c
    src/simulator/instructionExecutor/executors/BTypeExecutor/BTypeExecutor.c
    src/simulator/instructionExecutor/executors/RTypeExecutor/RTypeExecutor.c
    src/simulator/instructionExecutor/executors/ITypeExecutor/ITypeExecutor.c
    src/simulator/instructionExecutor/executors/JTypeExecutor/JTypeExecutor.c
    src/simulator/instructionExecutor/executors/STypeExecutor/STypeExecutor.c
    src/simulator/instructionExecutor/executors/UTypeExecutor/UTypeExecutor.c
)

# Add executable target
add_executable(simulator ${SOURCE_FILES})
