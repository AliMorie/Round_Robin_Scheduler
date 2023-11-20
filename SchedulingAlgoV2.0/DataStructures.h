#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

/// Enumeration of possible states of a process.
///
/// This enum defines the possible states of a process, including NEW, READY, RUNNING, and WAITING.
typedef enum
{
    NEW, ///< The process is new and has not started yet.
    READY, ///< The process is ready to be executed.
    RUNNING, ///< The process is currently running.
    WAITING ///< The process is waiting for a resource or event.
} Process_State_T;

/// Structure representing a process and its associated information.
///
/// This struct represents a process and contains various attributes such as its ID, arrival time,
/// CPU time, disk time, remaining CPU time, turnaround time, waiting time, file ID, and current state.
typedef struct
{
    int processID; ///< An integer representing the ID of the process.
    int arrivalTime; ///< An integer representing the arrival time of the process.
    int CPUTime; ///< An integer representing the CPU time required by the process.
    int diskTime; ///< An integer representing the disk time required by the process.
    int remainingCPUTime; ///< An integer representing the remaining CPU time of the process.
    int turnAroundTime; ///< An integer representing the turnaround time of the process.
    int waitingTime; ///< An integer representing the waiting time of the process.
    int fileID; ///< An integer representing the ID of the file associated with the process.
    Process_State_T state; ///< The current state of the process.
} Process_Struct;

/// Structure representing a queue data structure.
///
/// This struct represents a queue data structure used for storing processes.
/// It contains an array of processes, front and rear indices, and the size of the queue.
typedef struct
{
    Process_Struct* processes; ///< Pointer to an array of processes.
    int front; ///< The index of the front element in the queue.
    int rear; ///< The index of the rear element in the queue.
    int size; ///< The current size of the queue.
} Queue;

/// Structure representing a process simulator.
///
/// This struct represents a process simulator and contains various components such as CPU device queue,
/// disk device queue, clock value, quantum size, arrival queue, CPU scheduler queue, and disk scheduler queue.
typedef struct
{
    Queue CPUDevice; ///< The queue representing the CPU device.
    Queue DiskDevice; ///< The queue representing the disk device.
    int clock; ///< The current clock value of the process simulator.
    int quantum; ///< The quantum size for process execution.
    Queue ArrivalQueue; ///< The queue for storing arriving processes.
    Queue CPUScheduler; ///< The queue for CPU scheduling.
    Queue DiskScheduler; ///< The queue for disk scheduling.
} ProcessSimulator;

#endif // DATA_STRUCTURE_H