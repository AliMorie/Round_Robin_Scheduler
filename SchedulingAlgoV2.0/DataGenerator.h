/// @file DataGenerator.h
///	@brief The "DataGenerator.h" header file declares several functions related to data generation and random
///		   number generation. These functions are as follows:
/// @date 11/9/2023

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
///	## System Calls and Returns
///	1. open: Opens the output file for writing.
///		- Returns: If the file opening is successful, fopen returns a pointer to the FILE structure representing the
///		  opened file. If it fails to open the file, it returns NULL.
///	2. fprintf: Writes formatted data to the output file.
///	3. fclose: Closes the output file.
///		- Returns: fclose returns 0 on success and EOF (End-of-File) if an error occurs while closing the file.

/// @param inputFile The name of the output file to write the process data.
/// @param numProcesses The number of processes to generate data for.
/// @param fileId The ID of the file associated with the processes.
void generateProcessesData(const char* inputFile, const int numProcesses, const int fileId);
#endif // DATA_GENERATOR_H