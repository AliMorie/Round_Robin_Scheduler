#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DataStructures.h"
#include "DataGenerator.h"
#include "Evaluation.h"
#include "Scheduler.h"
#include "Helper.h"

int main(/*int argc, char* argv[]*/)
{
    // Check if the correct number of command-line arguments is provided
    // if (argc != 5)
    //{
    //    printf("Invalid number of arguments!\n");
    //    printf("Usage: ./simulator <number_of_processes> <input_file> <quantum> <output_trace_file>\n");
    //    return 1;
    //}

    //// Parse command-line arguments
    // const int numProcesses = atoi(argv[1]);
    // const char* inputFileName = argv[2];
    // const int quantum = atoi(argv[3]);
    // const char* outputFileName = argv[4];

    const int numProcesses = 10;
    const char* inputFileName = "input.txt";
    const int quantum = 3;
    const char* outputFileName = "output.csv";

    // Seed the random number generator
    srand(time(NULL));

    // Generate processes data and save it to a file
    generateProcessesData(inputFileName, numProcesses, 1);

    // Open the input file for reading
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        // Error handling if the file fails to open
        printf("Unable to create trace file.\n");
        return 0;
    }

    // Allocate memory for the array of processes
    Process_Struct* processes = malloc(numProcesses * sizeof(Process_Struct));

    // Read processes data from the input file
    readProcessesData(inputFile, processes, numProcesses);

    // Allocate memory for the process simulator
    ProcessSimulator* simulator = malloc(sizeof(ProcessSimulator));

    // Create the process simulator
    createSimulator(simulator, processes, numProcesses, quantum);

    // Simulate the processes and save the output to a file
    simulateProcesses(simulator, outputFileName);

    // Evaluate the algorithm
    EvaluateAlgo();

    // Free allocated memory
    free(simulator);
    free(processes);
    (void)(inputFile);

    return 0;
}