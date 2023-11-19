#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "DataStructures.h"

// The runCPUProcess function is responsible for executing a process on the CPU and applying the logic of utilizing 50%
// of CPU time before accessing the disk, incorporating the time quantum for Round-Robin scheduling.
// The function:
// 1- Dequeue a process from the CPU device queue using the dequeue function. This retrieves the next process to be
//	  executed on the CPU.
// 2- Calculate the CPU time required before accessing the disk by taking 50% (half) of the total
//	  CPU time of the process. This is done using the formula: const int cpuTimeBeforeDisk =
//    (int)ceil(process.CPUTime 2.0);.
// 3- Determine the remaining CPU time for the process by accessing the remainingCPUTime field of the process
//	 struct.
// 4- Check if the CPU time before accessing the disk (cpuTimeBeforeDisk) is less than or equal to the time
//	  quantum (simulator->quantum). If it is, it means the process will access the disk after utilizing 50% of its CPU
//	  time 	but before the time quantum expires.
// 5- If cpuTimeBeforeDisk is less than or equal to the time quantum:
//      - Print a message indicating that the process is running on the CPU for cpuTimeBeforeDisk units before accessing
//      the disk.
//      - Update the remaining CPU time for the process by subtracting cpuTimeBeforeDisk.
//      - Check if the remaining CPU time (remainingCPUTime) is less than or equal to the time quantum. If it is, the
//      process is preempted and put back in the CPU queue.
//      - If the remaining CPU time is greater than the time quantum, the process is preempted after using the time
//      quantum, and the remaining CPU time is updated accordingly.
//      - Set the state of the process as READY.
//      - Enqueue the process back into the CPU queue using the enqueueCPU function.
//      - Print a message indicating that the process is preempted after a certain number of units.
// 6- If cpuTimeBeforeDisk is greater than the time quantum:
//       - Print a message indicating that the process is running on the CPU for the remaining CPU time
//        (remainingCPUTime) units.
//       - Update the remaining CPU time for the process to 0, indicating that it has finished its execution.
//       - Set the state of the process as READY.
//       - Enqueue the process back into the CPU queue using the enqueueCPU function.
//       - Print a message indicating that the process has finished its execution.
void runCPUProcess(ProcessSimulator* simulator, FILE* outputTraceFile);

// This function simulates running a process on the disk device of the process simulator.
// The function dequeues a process from the disk device queue, sets its state to READY, sets its disk time to 0,
// increments the clock by 5, and enqueues it into the CPU device queue using the enqueueCPU function.
void runDiskProcess(ProcessSimulator* simulator);

// Simulates the execution of processes in the process simulator and generates an output trace file.
// The function iteratively executes the simulation until there are no processes remaining in any of the queues (arrival
// queue, CPU scheduler queue, CPU device queue, disk device queue). It performs the following steps:
//		- Checks and enqueues processes from the arrival queue into the CPU scheduler queue if their arrival time is less
//than 		or equal to the current clock time.
//		- Checks and runs processes on the CPU device by calling the runCPUProcess function.
//      - Checks and runs processes on the disk device by calling the runDiskProcess function.
//      - Schedules processes from the CPU scheduler queue to the CPU device queue.
//      - Schedules processes from the disk scheduler queue to the disk device queue. Increments the clock time by 1.
// The function also opens an output trace file(appending mode) specified by outputTraceFile and writes the simulation
// log into the file. If the file cannot be opened, an error message is printed to the console. Finally, the trace
// file is closed, and a success message is printed to the console indicating the successful generation of the output
// file.
void simulateProcesses(ProcessSimulator* simulator, const char* outputTraceFile);

// This function adds a process to the specified queue.
void enqueue(Queue* queue, Process_Struct process);

// This function removes and returns the front process from the specified queue.
Process_Struct dequeue(Queue* queue);

// This function enqueues a process into the CPU device queue of the process simulator.
void enqueueCPU(ProcessSimulator* simulator, Process_Struct process);

// This function enqueues a process into the disk device queue of the process simulator.
void enqueueDisk(ProcessSimulator* simulator, Process_Struct process);

// This function initializes a queue with the specified number of processes.
void initQueue(Queue* queue, int numProcesses);

// This function enqueues an array of processes into the arrival queue of the process simulator.
void enqueueArrivalQueue(ProcessSimulator* simulator, const Process_Struct* processes, int numProcesses);
#endif // SCHEDULER_H