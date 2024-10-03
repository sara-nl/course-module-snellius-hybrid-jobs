#!/bin/bash
#SBATCH -J axpy-hyb            # Job name
#SBATCH -o axpy-hyb-%j.log     # Output log file (%j will be replaced with job ID)
#SBATCH -e axpy-hyb-%j.log     # Error log file (%j will be replaced with job ID)
#SBATCH --nodes=1              # Number of nodes
#SBATCH --ntasks=128           # Total number of tasks (parallel processes)
#SBATCH --cpus-per-task=1      # Number of OpenMP threads per MPI task
#SBATCH --time=01:00:00        # Time limit (hh:mm:ss)

# Check if the N parameter was provided
if [ -z "$1" ]; then
    echo "Usage: sbatch submit-axpy.sh <N>"
    exit 1
fi

# Load necessary modules
module load 2023
module load foss/2023a

# Compile the program
mpicc -fopenmp axpy_parallel.c -o axpy_parallel

# Set the OMP_NUM_THREADS environment variable to match the cpus-per-task
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Execute the program with N passed as an argument
N=$1                           # Set the vector size from the first command line argument
srun ./axpy $N                 # Run the executable
