#include "Helper.h"
#include <stdio.h>
#include <stdlib.h>

#include "DataStructures.h"

int readProcessesData(FILE* sourceFile, Process_Struct* processes, const int numProcesses)
{
    if (processes == NULL)
    {
        printf("Memory allocation failed.\n");
        (void)fclose(sourceFile);
        return 0;
    }

    for (int i = 0; i < numProcesses; i++)
    {
        (void)fscanf_s(
            sourceFile,
            "%d %d %d %d %d",
            &processes[i].processID,
            &processes[i].fileID,
            &processes[i].arrivalTime,
            &processes[i].CPUTime,
            &processes[i].diskTime);
        processes[i].remainingCPUTime = processes[i].CPUTime;
        processes[i].turnAroundTime = 0;
        processes[i].waitingTime = 0;
        processes[i].state = NEW;
    }

    return 1;
}

void initQueue(Queue* queue, int numProcesses)
{
    queue->processes = malloc(numProcesses * sizeof(Process_Struct));
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

void enqueueArrivalQueue(ProcessSimulator* simulator, const Process_Struct* processes, const int numProcesses)
{
    for (int i = 0; i < numProcesses; ++i)
    {
        enqueue(&simulator->ArrivalQueue, processes[i]);
    }
}

void createSimulator(ProcessSimulator* simulator, const Process_Struct* processes, const int numProcesses, int quantum)
{
    const int maxProcesses = 10000;
    initQueue(&simulator->ArrivalQueue, maxProcesses);
    initQueue(&simulator->CPUScheduler, maxProcesses);
    initQueue(&simulator->DiskScheduler, maxProcesses);
    initQueue(&simulator->CPUDevice, maxProcesses);
    initQueue(&simulator->DiskDevice, maxProcesses);
    simulator->clock = 0;
    simulator->quantum = quantum;

    enqueueArrivalQueue(simulator, processes, numProcesses);
}

void clearFile(const char fileName[15])
{
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    (void)fclose(file);
}