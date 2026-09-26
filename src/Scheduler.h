/// @file Scheduler.h
///	@brief The "Scheduler.h" header file declares several functions related to process scheduling and simulation.
///	@author **Ali Merie**
/// @date 11/22/2023

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "DataStructures.h"

/// Runs a CPU process in the ProcessSimulator.
///
/// This function runs a CPU process in the ProcessSimulator by dequeuing a process from the CPU device queue,
/// updating its time slice and state based on certain conditions, and logging process metrics to the output file.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param outputFile A pointer to the output file where process metrics will be logged.
///
/// The `runCPUProcess()` function performs the following steps:
/// 1. Dequeues a process from the CPU device queue of the ProcessSimulator.
/// 2. Determines the time slice for the process by taking the minimum value between the quantum value
///    of the simulator and the remaining CPU time of the current process.
/// 3. Checks if the current process has finished all of its CPU time. If so:
///     - Updates the turnAroundTime of the process by subtracting its arrival time from the current clock value.
///     - Updates the waitingTime of the process by subtracting its CPU time from its turnAroundTime.
///     - Logs the processing details and other process metrics (quantum value, file ID, turnAroundTime, and
///       waitingTime)
///       to the output file using the fprintf() function.
/// 4. Checks if the current process has used at least 50% of its CPU time or if its disk time is zero.
///    If so, the process is considered to be in the waiting state. The following actions are performed:
///     - Updates the state of the process to WAITING.
///     - Decrements the remainingCPUTime of the process by the timeSlice value.
///     - Enqueues the process back into the CPU device queue.
/// 5. If the above conditions are not met, it means the process has finished its CPU time slice.
///       The following actions are performed:
///     - Updates the state of the process to READY.
///     - Enqueues the process into the disk device queue.
/// 6. Advances the clock of the simulator by the timeSlice value.
///
/// @note The runCPUProcess() function assumes that the queues (CPUDevice, CPUScheduler, DiskScheduler, DiskDevice)
///		  of the ProcessSimulator have been initialized properly.
void runCPUProcess(ProcessSimulator* simulator, FILE* outputFile);

/// Simulates the execution of processes in the ProcessSimulator.
///
/// This function simulates the execution of processes in the ProcessSimulator by continuously checking and
/// running processes on the CPU and Disk devices, scheduling processes from the arrival queue and CPU scheduler,
/// and updating the clock time. Process metrics are logged to the output trace file.
///
/// The `simulateProcesses()` function performs the following steps:
///		1. Determines the output trace file name. If the `outputTraceFile` parameter is NULL, "log.csv" is used as the
///		   default file name.
///		2. Tries to open the output trace file in append mode. If the file cannot be opened, an error message is
///		   displayed, and the function returns.
///		3. Enters a while loop that continues until all queues (ArrivalQueue, CPUScheduler, CPUDevice, DiskDevice) are
///        empty.
///		4. Inside the while loop, the following actions are performed:
///			- Checks and enqueues processes from the Arrival Queue to the CPU Scheduler if their arrival time is less
///		      than or equal to the current clock time.
///			- Checks and runs processes on the CPU by calling the `runCPUProcess()` function if the CPU device queue is
///		      not empty.
///			- Checks and runs processes on the Disk by calling the `runDiskProcess()` function if the Disk device queue
///			  is not empty.
///			- Schedules processes from the CPU Scheduler to the CPU by dequeuing processes and enqueuing them to the CPU
///			  Device queue if the CPU Device queue is empty and the CPU Scheduler queue is not empty.
///			- Schedules processes from the Disk Scheduler to the Disk by dequeuing a process and enqueuing it to the
///			  Disk Device queue if the Disk Device queue is empty and the Disk Scheduler queue is not empty.
///			- Increments the clock time of the simulator by one.
///		5. Once the while loop exits (all queues are empty), the output trace file is closed.
///		6. If the output trace file was successfully generated, a success message.
///
/// ## System Calls
/// 1. **fopen:** Returns a pointer to the FILE structure representing the opened file or NULL if an error occurs.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param outputTraceFile The output trace file path. If NULL, "log.csv" is used as the default file name.
/// Returns the minimum value between two integers.
void simulateProcesses(ProcessSimulator* simulator, const char* outputTraceFile);

/// Runs a disk process in the ProcessSimulator.
///
/// This function runs a disk process in the ProcessSimulator by dequeuing a process from the disk device queue,
/// updating its state and disk time, advancing the clock, and enqueuing it to the CPU device queue.
///
/// @param simulator A pointer to the ProcessSimulator.
void runDiskProcess(ProcessSimulator* simulator);

/// This function compares two integers and returns the smaller of the two.
///
/// @param a The first integer.
/// @param b The second integer.
/// @return The minimum value between a and b.
int minimum(int a, int b);

/// Enqueues a process into the CPU device queue of a ProcessSimulator.
///
/// This function enqueues a process into the CPU device queue of a ProcessSimulator
/// by adding it to the end of the queue.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param process The Process_Struct to be enqueued.
void enqueueCPU(ProcessSimulator* simulator, Process_Struct process);

/// Enqueues a process into the disk device queue of a ProcessSimulator.
///
/// This function enqueues a process into the disk device queue of a ProcessSimulator
/// by adding it to the end of the queue.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param process The Process_Struct to be enqueued.
void enqueueDisk(ProcessSimulator* simulator, Process_Struct process);

/// Schedules a process to the CPU scheduler queue of a ProcessSimulator.
///
/// This function schedules a process to the CPU scheduler queue of a ProcessSimulator
/// by adding it to the end of the queue.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param process The Process_Struct to be scheduled.
void scheduleCPUProcess(ProcessSimulator* simulator, Process_Struct process);

/// Schedules a process to the disk scheduler queue of a ProcessSimulator.
///
/// This function schedules a process to the disk scheduler queue of a ProcessSimulator
/// by adding it to the end of the queue.
///
/// @param simulator A pointer to the ProcessSimulator.
/// @param process The Process_Struct to be scheduled.
void scheduleDiskProcess(ProcessSimulator* simulator, Process_Struct process);

/// Rounds a double value to the nearest integer.
///
/// This function rounds a double value to the nearest integer using the standard rounding rule.
/// For example, 2.3 would be rounded to 2, and 2.7 would be rounded to 3.
///
/// @param value The double value to be rounded.
/// @return The rounded integer value.
int roundTime(double value);

#endif // SCHEDULER_H