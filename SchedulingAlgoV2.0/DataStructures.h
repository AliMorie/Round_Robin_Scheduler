#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

// This enum defines the possible states of a process. The states are NEW, READY, RUNNING, and WAITING.
typedef enum
{
    NEW,
    READY,
    RUNNING,
    WAITING
} Process_State_T;

// This struct represents a process and its associated information.
typedef struct
{
    int processID; // An integer representing the ID of the process.
    int arrivalTime; // An integer representing the arrival time of the process.
    int CPUTime; // An integer representing the CPU time required by the process.
    int diskTime; // An integer representing the disk time required by the process.
    int remainingCPUTime; // An integer representing the remaining CPU time of the process.
    int turnAroundTime; // An integer representing the turnaround time of the process.
    int waitingTime; // An integer representing the waiting time of the process.
    int fileID; // An integer representing the ID of the file associated with the process.
    Process_State_T state; // variable representing the current state of the process.
} Process_Struct;

// This struct represents a queue data structure.
typedef struct
{
    Process_Struct* processes;
    int front;
    int rear;
    int size;
} Queue;

// This struct represents a process simulator.
typedef struct
{
    Queue CPUDevice;
    Queue DiskDevice;
    int clock;
    int quantum;
    Queue ArrivalQueue;
    Queue CPUScheduler;
    Queue DiskScheduler;
} ProcessSimulator;

#endif // DATA_STRUCTURE_H