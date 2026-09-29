import pandas as pd
import matplotlib.pyplot as plt
from tabulate import tabulate

# Read the evaluation results
df = pd.read_csv('./log.csv')

# Average the waiting time and completion (turnaround) time of all
# processes for each quantum value tested in the evaluation
averages = df.groupby('quantum')[['waitingTime', 'turnAroundTime']].mean().reset_index()
averages.columns = ['Quantum', 'Average Waiting Time', 'Average Completion Time']

# Format the tables. showindex=False hides pandas' row numbers,
# which would otherwise appear as an extra unlabeled column
waiting_time_table = tabulate(averages[['Quantum', 'Average Waiting Time']],
                              headers='keys', tablefmt='fancy_grid', showindex=False)
completion_time_table = tabulate(averages[['Quantum', 'Average Completion Time']],
                                 headers='keys', tablefmt='fancy_grid', showindex=False)

# Print the table for average waiting time
print("Average Waiting Time:")
print(waiting_time_table)

# Print the table for average completion time
print("\nAverage Completion Time:")
print(completion_time_table)


def save_table_image(table_text, file_name):
    """Render a text table into a PNG image."""
    fig, ax = plt.subplots()
    ax.axis('off')

    # A monospace font keeps the table's columns and borders aligned
    ax.text(0.5, 0.5, table_text, ha='center', va='center', fontsize=12, family='monospace', linespacing=1.0)

    # bbox_inches='tight' fits the image to the table, so long tables aren't cut off
    fig.savefig(file_name, dpi=200, bbox_inches='tight')
    plt.close(fig)


# Save both tables as PNG images
save_table_image(waiting_time_table, 'waiting_time_table.png')
save_table_image(completion_time_table, 'completion_time_table.png')