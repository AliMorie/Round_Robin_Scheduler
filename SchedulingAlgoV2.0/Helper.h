#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#include "DataStructures.h"

#define ARRIVAL_RATE 0.5
#define MEAN_CPU_TIME 10.0
#define STDDEV_CPU_TIME 1.0
#define MEAN_DISK_TIME 5.0
#define STDDEV_DISK_TIME 0.5

/// Reads process data from a source file and populates an array of Process_Struct.
///
/// This function reads process data from a source file and populates an array of Process_Struct
/// with the read values. Each line in the source file represents a process and is expected to
/// follow the format: "processID fileID arrivalTime CPUTime diskTime".
///
/// \param sourceFile A pointer to the source file from which the process data will be read.
/// \param processes An array of Process_Struct where the read process data will be stored.
/// \param numProcesses The number of processes to read from the file.
///
/// \return 1 if the reading and populating process was successful, 0 if there was a memory allocation failure
///         or an issue with closing the source file.
int readProcessesData(FILE* sourceFile, Process_Struct* processes, const int numProcesses);

/// Initializes a queue structure.
///
/// This function initializes a Queue structure by allocating memory for the processes array
/// and setting the front, rear, and size values.
///
/// \param queue A pointer to the Queue structure to be initialized.
/// \param numProcesses The number of processes in the queue.
void initQueue(Queue* queue, int numProcesses);


/// Enqueues the processes from an array into the arrival queue of a ProcessSimulator.
///
/// This function enqueues the processes from an array of Process_Struct into the arrival queue
/// of a ProcessSimulator. The processes are added to the end of the arrival queue.
///
/// \param simulator A pointer to the ProcessSimulator.
/// \param processes An array of Process_Struct to be enqueued.
/// \param numProcesses The number of processes in the array.
void enqueueArrivalQueue(ProcessSimulator* simulator, const Process_Struct* processes, const int numProcesses);


/// Creates a ProcessSimulator instance.
///
/// This function creates a ProcessSimulator instance by initializing the various queues and
/// setting the clock and quantum values.
///
/// \param simulator A pointer to the ProcessSimulator to be created.
/// \param processes An array of Process_Struct representing the processes.
/// \param numProcesses The number of processes in the array.
/// \param quantum The quantum value for the simulator.
void createSimulator(
    ProcessSimulator* simulator,
    const Process_Struct* processes,
    const int numProcesses,
    const int quantum);


/// Clears the content of a file.
///
/// This function clears the content of a file by opening it in write mode and immediately closing it.
///
/// \param fileName The name of the file to be cleared.
void clearFile(const char fileName[15]);


/// Enqueues a process into a queue.
///
/// This function enqueues a process into a queue by adding it to the end of the queue.
///
/// \param queue A pointer to the Queue.
/// \param process The Process_Struct to be enqueued.
void enqueue(Queue* queue, Process_Struct process);


/// Dequeues a process from a queue.
///
/// This function dequeues a process from a queue by removing and returning the process at the front of the queue.
///
/// \param queue A pointer to the Queue.
/// \return The dequeued Process_Struct.
Process_Struct dequeue(Queue* queue);
;

#endif // HELPER_H