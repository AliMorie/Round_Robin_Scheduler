#include "DataStructures.h"

#include <stdio.h>
#include <stdlib.h>

#include "Helper.h"

int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

void enqueueCPU(ProcessSimulator* simulator, Process_Struct process)
{
    enqueue(&simulator->CPUDevice, process);
}

void enqueueDisk(ProcessSimulator* simulator, Process_Struct process)
{
    enqueue(&simulator->DiskDevice, process);
}

void scheduleCPUProcess(ProcessSimulator* simulator, Process_Struct process)
{
    enqueue(&simulator->CPUScheduler, process);
}

void scheduleDiskProcess(ProcessSimulator* simulator, Process_Struct process)
{
    enqueue(&simulator->DiskScheduler, process);
}

int roundTime(double value)
{
    return (int)(value + 0.5);
}

void runCPUProcess(ProcessSimulator* simulator, FILE* outputFile)
{
    Process_Struct currentProcess = dequeue(&simulator->CPUDevice);

    // set the time slice that the process will spend in the processor.
    const int timeSlice = minimum(simulator->quantum, currentProcess.remainingCPUTime);

    // Check if process has finished all of its CPU time.
    if (currentProcess.remainingCPUTime <= 0)
    {
        // Update turnAroundTime
        currentProcess.turnAroundTime = simulator->clock - currentProcess.arrivalTime;

        // Update waitingTime
        currentProcess.waitingTime = currentProcess.turnAroundTime - currentProcess.CPUTime;

        // Log processing details and other process metrics for further analysis.
        (void)fprintf(
            outputFile,
            "%d,%d,%d,%d\n",
            simulator->quantum,
            currentProcess.fileID,
            currentProcess.turnAroundTime,
            currentProcess.waitingTime);
    }
    // Check if process has used 50% of its CPU time
    else if (currentProcess.remainingCPUTime >= roundTime(currentProcess.CPUTime / 2.0) || currentProcess.diskTime <= 0)
    {
        currentProcess.state = WAITING;
        currentProcess.remainingCPUTime -= timeSlice;
        enqueueCPU(simulator, currentProcess);
    }
    // The process has finished the CPU time slice  assigned to it.
    else
    {
        currentProcess.state = READY;
        enqueueDisk(simulator, currentProcess);
    }

    simulator->clock += timeSlice;
}

void runDiskProcess(ProcessSimulator* simulator)
{
    Process_Struct currentProcess = dequeue(&simulator->DiskDevice);

    currentProcess.diskTime = 0;
    simulator->clock += 5;
    enqueueCPU(simulator, currentProcess);
}

void simulateProcesses(ProcessSimulator* simulator, const char* outputTraceFile)
{
    const char* fileName = (outputTraceFile == NULL) ? "log.csv" : outputTraceFile;

    // If the evaluator is running
    FILE* traceFile = fopen(fileName, "a");

    // could not open the file
    if (traceFile == NULL)
    {
        printf("Unable to create trace file.\n");
        return;
    }

    while (simulator->ArrivalQueue.size > 0 || simulator->CPUScheduler.size > 0 || simulator->CPUDevice.size > 0
           || simulator->DiskDevice.size > 0)
    {
        // Check and enqueue processes from the Arrival Queue
        while (simulator->ArrivalQueue.size > 0
               && simulator->ArrivalQueue.processes[simulator->ArrivalQueue.front].arrivalTime <= simulator->clock)
        {
            Process_Struct process = dequeue(&simulator->ArrivalQueue);
            process.state = READY;
            scheduleCPUProcess(simulator, process);
        }

        // Check and run processes on the CPU
        if (simulator->CPUDevice.size > 0)
        {
            runCPUProcess(simulator, traceFile);
        }

        // Check and run processes on the Disk
        if (simulator->DiskDevice.size > 0)
        {
            runDiskProcess(simulator);
        }

        // Schedule processes from the CPU Scheduler to the CPU
        while (simulator->CPUScheduler.size > 0 && simulator->CPUDevice.size == 0)
        {
            Process_Struct process = dequeue(&simulator->CPUScheduler);
            process.state = RUNNING;
            enqueueCPU(simulator, process);
        }

        // Schedule processes from the Disk Scheduler to the Disk
        if (simulator->DiskDevice.size == 0 && simulator->DiskScheduler.size > 0)
        {
            Process_Struct process = dequeue(&simulator->DiskScheduler);
            process.state = WAITING;
            enqueueDisk(simulator, process);
        }

        // Increment clock time
        simulator->clock++;
    }

    (void)fclose(traceFile);
    printf("Output file generated successfully.\n");
}
