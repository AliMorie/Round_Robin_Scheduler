#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DataStructures.h"
#include "DataGenerator.h"
#include "Evaluation.h"
#include "Scheduler.h"
#include "Helper.h"

int main(int argc, char* argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 5)
    {
        printf("Invalid number of arguments!\n");
        printf("Usage: ./simulator <number_of_processes> <input_file> <quantum> <output_trace_file>\n");
        return 1;
    }

    // Parse command-line arguments
    const int numProcesses = atoi(argv[1]);
    const char* inputFileName = argv[2];
    const int quantum = atoi(argv[3]);
    const char* outputFileName = argv[4];

    // Seed the random number generator
    srand(time(NULL));

    // Generate processes data and save it to a file
    generateProcessesData(inputFileName, numProcesses, 1);

    // Open the input file for reading
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        printf("Unable to create trace file.\n");
        return 0;
    }

    Process_Struct* processes = malloc(numProcesses * sizeof(Process_Struct));
    readProcessesData(inputFile, processes, numProcesses);

    ProcessSimulator* simulator = malloc(sizeof(ProcessSimulator));
    createSimulator(simulator, processes, numProcesses, quantum);

    simulateProcesses(simulator, outputFileName);

    EvaluateAlgo();

    free(simulator);
    free(processes);
    fclose(inputFile);  // was missing before — you had `(void)(inputFile);` which does nothing

    return 0;
}