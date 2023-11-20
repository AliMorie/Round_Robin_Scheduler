import pandas as pd
from tabulate import tabulate

# Read the CSV file and load the dataset
df = pd.read_csv('./SchedulingAlgoV2.0/log.csv')

# Group the entries by quantum value and calculate the average waiting time and completion time for each quantum value
grouped = df.groupby('quantum').mean()

# Create an empty DataFrame to store the averaged results
averaged_results = pd.DataFrame(columns=['Quantum', 'Average Waiting Time', 'Average Completion Time'])

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

    # Append the averaged results to the DataFrame
    averaged_results = pd.concat([averaged_results, pd.DataFrame({'Quantum': quantum, 'Average Waiting Time': avg_waiting_time, 'Average Completion Time': avg_completion_time}, index=[0])], ignore_index=True)

# Format the tables
waiting_time_table = tabulate(averaged_results[['Quantum', 'Average Waiting Time']], headers='keys', tablefmt='fancy_grid')
completion_time_table = tabulate(averaged_results[['Quantum', 'Average Completion Time']], headers='keys', tablefmt='fancy_grid')

# Print the table for average waiting time
print("Average Waiting Time:")
print(waiting_time_table)

# Print the table for average completion time
print("\nAverage Completion Time:")
print(completion_time_table)

# Create a new figure and axis
fig, ax = plt.subplots()

# Hide the axis and set the text output
ax.axis('off')
ax.text(0.5, 0.5, waiting_time_table, ha='center', va='center', fontsize=12)

# Save the figure as a PNG image
fig.savefig('waiting_time_table.png', dpi=1000)

# Create a new figure and axis
fig, ax = plt.subplots()

# Hide the axis and set the text output
ax.axis('off')
ax.text(0.5, 0.5, completion_time_table, ha='center', va='center', fontsize=12)

# Save the figure as a PNG image
fig.savefig('completion_time_table.png', dpi=1000)