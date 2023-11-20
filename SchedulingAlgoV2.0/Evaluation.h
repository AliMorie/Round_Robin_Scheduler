#ifndef UNTITLED_EVALUATION_H
#define UNTITLED_EVALUATION_H

/// Evaluates an algorithm by running simulations with different quantum values.
///
/// This function evaluates an algorithm by running simulations with different quantum values.
/// It performs the following steps:
///
/// 1. Generates input trace files using the `generateProcessesData` function.
///    The number of trace files and the number of processes per file are pre-defined constants.
///    The trace files are named "trace1.txt" to "trace5.txt".
///
/// 2. Clears the previously logged file by calling the `clearFile` function.
///    This ensures that the new log file will contain only the latest results.
///
/// 3. Opens the log file for writing. If the file cannot be opened, an error message is printed, and the function
/// returns.
///    The log file is named "log.csv".
///
/// 4. Writes the header to the log file, consisting of the column names: "quantum", "fileID", "turnAroundTime", and
/// "waitingTime".
///
/// 5. Closes the log file.
///
/// 6. Runs experiments for each quantum value within the specified range.
///    The range is defined by the constants `minQuantum` and `maxQuantum`.
///
///    For each quantum value:
///    - Runs each trace file using a nested loop.
///      - Loads the trace file and populates an array of `Process_Struct` by calling `readProcessesData`.
///        If the trace file cannot be loaded, an error message is printed, and the function continues with the next
///        trace file.
///      - Creates a `ProcessSimulator` instance by calling `createSimulator` with the loaded processes, the number of
///      processes,
///        and the current quantum value.
///      - Runs the simulation by calling `simulateProcesses` with the process simulator and `NULL` as the output file.
///      - Closes the input file and frees the allocated memory for the processes and the simulator.
///
/// The function evaluates the algorithm's performance by running simulations with different quantum values and logging
/// the results. The results are stored in the log file "log.csv" in CSV format, with each row representing a
/// combination of quantum value, trace file ID, turnaround time, and waiting time.
///
/// Note: The function assumes that the necessary functions (`generateProcessesData`, `clearFile`, `readProcessesData`,
/// `createSimulator`, `simulateProcesses`) are defined and implemented correctly.
void EvaluateAlgo();

#endif // UNTITLED_EVALUATION_H
