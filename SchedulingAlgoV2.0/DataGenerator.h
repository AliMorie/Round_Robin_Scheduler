#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

// Takes a double value as input and rounds it to the nearest integer.
int roundToNearestInteger(double value);

// Generates a random arrival time based on a Poisson distribution with the given lambda parameter.
int generatePoissonArrival(double lambda);

// Generates a random value from a log-normal distribution with the given mean and standard deviation.
int generateLogNormal(double mean, double stddev, int numInputFiles);

// Generates process data and writes it to an input file. The function creates an input file with the specified name
// and writes process data to it. It also prints a success message to the console.
void generateProcessesData(const char* inputFile, int numProcesses, int fileId);

#endif // DATA_GENERATOR_H