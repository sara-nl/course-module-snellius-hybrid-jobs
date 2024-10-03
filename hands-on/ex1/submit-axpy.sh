#!/bin/bash
#SBATCH -J axpy                # Job name
#SBATCH -o axpy-%j.out         # Output log file (%j will be replaced with job ID)
#SBATCH -e axpy-%j.err         # Error log file (%j will be replaced with job ID)
#SBATCH --nodes=1              # Number of nodes
#SBATCH --ntasks=1             # Total number of tasks (parallel processes)
#SBATCH --ntasks-per-node=1    # Number of tasks per node
#SBATCH --cpus-per-task=1      # Number of CPU cores per task
#SBATCH --time=01:00:00        # Time limit (hh:mm:ss)

# Check if the N parameter was provided
if [ -z "$1" ]; then
    echo "Usage: sbatch submit-axpy.sh <N>"
    exit 1
fi

# Load necessary modules
module load 2023               # Load the specific environment (update as needed)
module load foss/2023a         # Load the desired compiler/toolchain (update as needed)

# Compile the program
gcc axpy.c -o axpy

# Execute the program with N passed as an argument
N=$1                           # Set the vector size from the first command line argument
srun ./axpy $N                 # Run the executable
