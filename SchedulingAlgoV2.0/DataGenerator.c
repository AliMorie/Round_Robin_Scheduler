/// @file DataGenerator.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "DataGenerator.h"
#include "Helper.h"

int roundToNearestInteger(double value)
{
    return (int)(value + 0.5);
}

int generatePoissonArrival(double lambda)
{
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;
    double arrivalTime = 0.0;

    // Generate arrival time according to the Poisson distribution
    do
    {
        k++;
        p *= (double)rand() / (double)RAND_MAX;
    } while (p > L);

    arrivalTime = (double)k - 1.0;

    // Round the arrival time to the nearest integer
    return roundToNearestInteger(arrivalTime);
}

int generateLogNormal(double mean, double stddev)
{
    double mu = log(mean * mean / sqrt(stddev * stddev + mean * mean));
    double sigma = sqrt(log(1.0 + stddev * stddev / (mean * mean)));

    // Generate a random value from the log-normal distribution
    double z = mu + sigma * (double)rand() / (double)RAND_MAX;
    const double value = round(exp(z));

    // Round the generated value to the nearest integer
    return roundToNearestInteger(value);
}

void generateProcessesData(const char* inputFile, const int numProcesses, const int fileId)
{
    // Open the output file for writing
    FILE* outputFile = fopen(inputFile, "w");
    if (outputFile == NULL)
    {
        printf("Unable to create input file.\n");
        return;
    }

    int arrivalTime = 0;
    int cpuTime = 0;
    int diskTime = 0;

    // Generate data for each process
    for (int processID = 1; processID <= numProcesses; processID++)
    {
        // Generate arrival time using a Poisson distribution
        arrivalTime += generatePoissonArrival(ARRIVAL_RATE);

        // Generate CPU time using a log-normal distribution
        cpuTime = generateLogNormal(MEAN_CPU_TIME, STDDEV_CPU_TIME);

        // Generate disk time using a log-normal distribution
        diskTime = generateLogNormal(MEAN_DISK_TIME, STDDEV_DISK_TIME);

        // Write the process data to the output file
        (void)fprintf(outputFile, "%d %d %d %d %d\n", processID, fileId, arrivalTime, cpuTime, diskTime);
    }

    // Close the output file
    (void)fclose(outputFile);

    printf("Input file generated successfully.\n");
}