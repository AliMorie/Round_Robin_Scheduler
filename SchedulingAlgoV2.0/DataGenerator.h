/// @file DataGenerator.h

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

/// Rounds a double value to the nearest integer.
///
/// This function takes a double value and rounds it to the nearest integer using the
/// "round half up" method. For example, 1.4 would be rounded to 1, and 3.6 would be rounded to 4.
///
/// @param value The double value to be rounded.
/// @return The nearest integer value after rounding.
int roundToNearestInteger(double value);

/// Generates a random value according to the Poisson distribution.
///
/// This function generates a random value that follows the Poisson distribution with the given
/// arrival rate lambda. The algorithm used is based on the Knuth Poisson random number generator.
///
/// @param lambda The arrival rate parameter of the Poisson distribution.
/// @return A random integer value generated according to the Poisson distribution.
int generatePoissonArrival(double lambda);

/// Generates a random value according to the log-normal distribution.
///
/// This function generates a random value that follows the log-normal distribution with the given
/// mean and standard deviation. The algorithm used transforms the log-normal distribution into a
/// normal distribution and then applies the inverse log transformation.
///
/// @param mean The mean of the log-normal distribution.
/// @param stddev The standard deviation of the log-normal distribution.
/// @return A random integer value generated according to the log-normal distribution.
int generateLogNormal(double mean, double stddev);

/// Generates data for a group of processes and writes it to an output file.
///
/// This function generates arrival time, CPU time, and disk time data for a specified number of processes.
/// The generated data is written to the specified output file in the format:
/// "processID fileId arrivalTime cpuTime diskTime".
///
/// @param inputFile The name of the output file to write the process data.
/// @param numProcesses The number of processes to generate data for.
/// @param fileId The ID of the file associated with the processes.
void generateProcessesData(const char* inputFile, const int numProcesses, const int fileId);
#endif // DATA_GENERATOR_H