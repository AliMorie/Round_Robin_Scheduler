import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file and load the dataset
df = pd.read_csv('./log.csv')

# Group the entries by quantum value and calculate the average waiting time and completion time for each quantum value
grouped = df.groupby('quantum').mean()

# Create empty lists to store the averaged results
averaged_waiting_time = []
averaged_completion_time = []

# Iterate over the quantum values
for quantum in range(1, 11):
    # Select the entries for the current quantum value
    quantum_entries = df[df['quantum'] == quantum]

    # Initialize variables to store the sum of waiting time and completion time for 5 entries
    waiting_sum = 0
    completion_sum = 0

    # Iterate over the entries in groups of 5
    for i in range(0, len(quantum_entries), 5):
        # Select the 5 entries for averaging
        entries = quantum_entries[i:i+5]

        # Calculate the sum of waiting time and completion time for the selected entries
        waiting_sum += entries['waitingTime'].sum()
        completion_sum += entries['turnAroundTime'].sum()

    # Calculate the average waiting time and completion time for the current quantum value
    avg_waiting_time = waiting_sum / len(quantum_entries)
    avg_completion_time = completion_sum / len(quantum_entries)
    
    # Append the averaged results to the lists
    averaged_waiting_time.append(avg_waiting_time)
    averaged_completion_time.append(avg_completion_time)

# Create a list of quantum values from 1 to 10
quantum_values = list(range(1, 11))

# Plot the results
plt.plot(quantum_values, averaged_waiting_time, label='Average Waiting Time')
plt.plot(quantum_values, averaged_completion_time, label='Average Completion Time')
plt.xlabel('Quantum')
plt.ylabel('Time')
plt.title('SchedulingResultAnalysis_1.png')
plt.legend()
plt.show()

# Save the plot to a file
plt.savefig("Average Waiting Time and Completion Time VS. Quantum Value.png")