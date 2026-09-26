#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DataGenerator.h"
#include "DataStructures.h"
#include "Evaluation.h"
#include "Helper.h"
#include "Scheduler.h"

void EvaluateAlgo()
{
    const char logFIle[15] = "log.csv";
    const int numTraceFiles = 5;
    const int numProcesses = 50;
    const int minQuantum = 1;
    const int maxQuantum = 30;

    char traceFileNames[5][20] = {"trace1.txt", "trace2.txt", "trace3.txt", "trace4.txt", "trace5.txt"};

    // Initialize a random seed for random numbers generation
    srand(time(NULL));

    // Generate input trace files
    for (int i = 0; i < numTraceFiles; i++)
    {
        generateProcessesData(traceFileNames[i], numProcesses, i + 1);
    }

    // Clear the previously logged file So that we can log the new ones.
    clearFile(logFIle);

    // Open the log file for writing
    FILE* file = fopen("log.csv", "w");
    if (file == NULL)
    {
        printf("Unable to create trace file.\n");
        return;
    }

    // Write the header to the log file.
    (void)fprintf(file, "%s,%s,%s,%s\n", "quantum", "fileID", "turnAroundTime", "waitingTime");

    // Close the log file
    (void)fclose(file);

    // Run experiments for each quantum value
    for (int quantum = minQuantum; quantum <= maxQuantum; quantum++)
    {
        // Run each trace file for the current quantum
        for (int i = 0; i < numTraceFiles; i++)
        {
            // Load the trace files and populate the processes
            Process_Struct* processes = malloc(numProcesses * sizeof(Process_Struct));
            FILE* inputFile = fopen(traceFileNames[i], "r");
            if (inputFile == NULL)
            {
                return;
            }

            // Read process data from the input file
            if (!readProcessesData(inputFile, processes, numProcesses))
            {
                printf("Error loading trace file: %s\n", traceFileNames[i]);
                free(processes);
                continue;
            }

            // Create a process simulator
            ProcessSimulator* simulator = malloc(numProcesses * sizeof(ProcessSimulator));
            createSimulator(simulator, processes, numProcesses, quantum);

            // Run the simulation.
            simulateProcesses(simulator, NULL);

            // Close the input file and free the allocated memory
            (void)fclose(inputFile);
            free(processes);
            free(simulator);
        }
    }
}