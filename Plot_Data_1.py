import pandas as pd
import matplotlib.pyplot as plt

# Read the evaluation results
df = pd.read_csv('./log.csv')

# Average the waiting time and completion (turnaround) time of all
# processes for each quantum value tested in the evaluation
averages = df.groupby('quantum')[['waitingTime', 'turnAroundTime']].mean()

# Use the quantum values actually present in the log for the x-axis,
# so the plot adapts to whatever range the evaluation tested
quantum_values = averages.index

# Plot the results
plt.plot(quantum_values, averages['waitingTime'], label='Average Waiting Time')
plt.plot(quantum_values, averages['turnAroundTime'], label='Average Completion Time')
plt.xlabel('Quantum')
plt.ylabel('Time')
plt.title('Average Waiting Time and Completion Time vs. Quantum Value')
plt.legend()

# Save before showing: closing the plot window clears the figure,
# so saving afterwards would produce an empty image
plt.savefig("SchedulingResultAnalysis_1.png")
plt.show()