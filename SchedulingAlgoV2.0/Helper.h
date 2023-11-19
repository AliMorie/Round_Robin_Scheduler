#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#include "DataStructures.h"

#define ARRIVAL_RATE 0.5
#define MEAN_CPU_TIME 10.0
#define STDDEV_CPU_TIME 1.0
#define MEAN_DISK_TIME 5.0
#define STDDEV_DISK_TIME 0.5

void createSimulator(ProcessSimulator* simulator, Process_Struct* processes, int numProcesses, int quantum);
int readProcessesData(FILE* sourceFile, Process_Struct* processes, int numProcesses);
void clearFile(const char fileName[15]);
#endif // HELPER_H