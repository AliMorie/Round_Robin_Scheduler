import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('./SchedulingAlgoV2.0/log.csv')

# Calculate the average waiting time and completion time for each quantum value and file ID
avg_waiting_time = df.groupby(['quantum', 'fileID'])['waitingTime'].mean().reset_index()
avg_completion_time = df.groupby(['quantum', 'fileID'])['turnAroundTime'].mean().reset_index()

# Group the data by quantum and calculate the average of 5 entries for each quantum value
avg_waiting_time_grouped = avg_waiting_time.groupby('quantum')['waitingTime'].mean()
avg_completion_time_grouped = avg_completion_time.groupby('quantum')['turnAroundTime'].mean()

# Calculate the average of 5 entries for each quantum value
avg_waiting_time_averaged = avg_waiting_time_grouped.groupby('quantum').rolling(window=5, min_periods=1).mean().reset_index(drop=True)
avg_completion_time_averaged = avg_completion_time_grouped.groupby('quantum').rolling(window=5, min_periods=1).mean().reset_index(drop=True)

# Plot the average waiting time and average completion time on the same graph
plt.plot(range(1, 11), avg_waiting_time_averaged, marker='o', label='Average Waiting Time', color='blue')
plt.plot(range(1, 11), avg_completion_time_averaged, marker='o', label='Average Completion Time', color='red')
plt.xlabel('Quantum Value')
plt.ylabel('Time')
plt.title('Average Waiting Time and Completion Time vs. Quantum Value')
plt.legend()
plt.show()

# Save the plot to a file
plt.savefig("SchedulingResultAnalysis_2.png")