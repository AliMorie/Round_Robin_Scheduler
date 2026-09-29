import pandas as pd
import matplotlib.pyplot as plt

# Read the evaluation results
df = pd.read_csv('./log.csv')

# Average each trace file's results per quantum first, then average
# across the files, so every trace file carries equal weight
per_file = df.groupby(['quantum', 'fileID'])[['waitingTime', 'turnAroundTime']].mean()
per_quantum = per_file.groupby(level='quantum').mean()

# Use the quantum values actually present in the log for the x-axis,
# so the plot adapts to whatever range the evaluation tested
quantums = per_quantum.index

# Plot the average waiting time and average completion time on the same graph
plt.plot(quantums, per_quantum['waitingTime'], marker='o', label='Average Waiting Time', color='blue')
plt.plot(quantums, per_quantum['turnAroundTime'], marker='o', label='Average Completion Time', color='red')
plt.xlabel('Quantum Value')
plt.ylabel('Time')
plt.title('Average Waiting Time and Completion Time vs. Quantum Value')
plt.legend()

# Save before showing: closing the plot window clears the figure,
# so saving afterwards would produce an empty image
plt.savefig("SchedulingResultAnalysis_2.png")
plt.show()
